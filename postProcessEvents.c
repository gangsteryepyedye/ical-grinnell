 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "calEnum.h"
#include "enumFunctions.h"
#include "dataStructures.h"
#include "postProcessEvents.h"

//NOTE THESE FUNCTIONS ARE NOT YET COMPLETE, THEY ARE MOSTLY JUST STUBS
//

bool eventSpansTwoDays(event_node *event, configuration_info *configInfo){
  bool result;
  //we test to see if the event start and ends on the same day of the year,
  //and because an event could potentially be a year or more long(unlikely)
  //we make sure it is also in the same year
  result = (event->st->tm_yday == event->et->tm_yday) && (event->st->tm_year == event->et->tm_year);
  return !result;
}

void splitEvent(event_node *event, configuration_info *configInfo){
  event_node * newEvent;
  newEvent = (event_node *) malloc( sizeof(event_node));
  newEvent->st = (struct tm *) malloc(1 * sizeof(struct tm));
  newEvent->et = (struct tm *) malloc(1 * sizeof(struct tm));
  newEvent->summary = (char *) malloc(31 * sizeof(char));
  newEvent->location = (char *) malloc(31 * sizeof(char));
  newEvent->timeString = (char *) malloc(31 * sizeof(char));
  newEvent->options = (node_options *) malloc(1 * sizeof(node_options));

  memcpy(newEvent->st, event->st, sizeof(struct tm));
  memcpy(newEvent->et, event->et, sizeof(struct tm));

  //Make the original event terminate at 11:59:59 of the day it begins
  //strictly speaking this will be slightly incorrect when there are leap 
  //seconds added, but this will have not impact on the printed output
  event->et->tm_sec = 59;
  event->et->tm_min = 59;
  event->et->tm_hour = 23;
  event->et->tm_mday += event->st->tm_mday;

  //Make the new event begin at 0:00:00 of the next day
  newEvent->st->tm_sec = 0;
  newEvent->st->tm_min = 0;
  newEvent->st->tm_hour = 0;
  newEvent->st->tm_mday += 1;

  //this both normalizes st( so that mach 32 ==> april 1) and fills in the start_time
  //field of the new event
  newEvent->start_time = mktime(newEvent->st);
  //update end_time in the original event
  event->end_time = mktime(event->et);

  //strictly speaking we could have the new event point to the old string, however
  //in terms of cleaning up the structures at the end we probably want each of the
  //events to have seperate strings
  strncpy(newEvent->summary, event->summary, 30 * sizeof(char));
  strncpy(newEvent->location, event->location, 30 * sizeof(char));  
  newEvent->summary[30] ='\0';
  newEvent->location[30] ='\0';


  event_node * tmp;
  tmp = event;
  if(tmp->next_event == NULL){
    tmp->next_event = newEvent;
    newEvent->next_event = NULL;
  }
  else{
    //as long as the next event in the list starts before the new split event 
    //go to the next node, this is only the case if events can overlap, I am not 
    //sure if we are going to allow this, but just in case.
    //otherwise we could have just inserted it directly after the event it seperated from 
    while(difftime(tmp->next_event->start_time, newEvent->start_time) < 0){
      tmp = tmp->next_event;
    }
    newEvent->next_event = tmp->next_event;
    tmp->next_event = newEvent;
  }
    
}

void setFonts(event_node *event, configuration_info *configInfo){
  event->options->time_font = configInfo->timeFont;
  event->options->summary_font = configInfo->summaryFont;
  event->options->location_font = configInfo->locationFont;
}

void setColors(event_node *event, configuration_info *configInfo){
  event->options->box_color = configInfo->defaultBoxColor;
  event->options->text_color = configInfo->defaultFontColor;

}


void truncateTime(event_node *event, configuration_info *configInfo){

}

void addTimeString(event_node *event, bool twentyFourHourTime){
  int startHour, endHour;
  if(twentyFourHourTime){
    sprintf(event->timeString,"%d:%02d-%d:%02d",event->st->tm_hour,event->st->tm_min, event->et->tm_hour, event->et->tm_min);
  }
  else{
    startHour = event->st->tm_hour;
    endHour = event->et->tm_hour;
    if(startHour > 12){
      startHour -= 12;//if the hour is after 12, we subtract 12, ie 13 becomes 1
    }
    if(startHour == 0){
      startHour = 12; //the 0th hour is displayed as 12
    }
    if(endHour > 12){
      endHour -= 12;
    }
    if(endHour == 0){
      endHour = 12;
    }
    sprintf(event->timeString,"%d:%02d-%d:%02d",startHour,event->st->tm_min, endHour, event->et->tm_min);
  }
}

/* void applySummaryRules(event_node *event, configuration_info configInfo){ */
/*   ruleNode *curRule = configInfo->summaryRules; */
/*   while(curRule != NULL){ */
/*     if(!strcmp( curRule->antecedent, event->summary)){ */
      

int evaluateAntecedent(event_node *event, ruleNode *rule){
  switch(rule->raf)
    {
    case SUMMARY:
      return !strcmp(event->summary, rule->antecedentValue);
      break;
    case LOCATION:
      return !strcmp(event->location, rule->antecedentValue);
      break;
    case TIME:
      return !strcmp(event->timeString, rule->antecedentValue);
      break;
    default:
      return 0;
    }
}
 

void setConsequent(event_node *event, ruleNode *rule){
  switch(rule->rcf)
    {
    case BOX_COLOR:
      event->options->box_color = colorStringToInt(rule->consequentValue);
      break;
    case TEXT_COLOR:
      event->options->text_color = colorStringToInt(rule->consequentValue);
      break;
    case TIME_FONT:
      event->options->time_font = fontStringToInt(rule->consequentValue);
      break;
    case SUMMARY_FONT:
      event->options->summary_font = fontStringToInt(rule->consequentValue);
      break;
    case LOCATION_FONT:
      event->options->location_font = fontStringToInt(rule->consequentValue);
      break;
    default:
      printf("SOMETHING WENT WRONG\n");
      
    }
}
void applyRules(event_node *event, configuration_info *configInfo){
  ruleNode *curRule = configInfo->rules;
  while(curRule != NULL){
    if(evaluateAntecedent(event, curRule)){
      setConsequent(event, curRule);
    }
    curRule = curRule->nextRule;
  }
}
void postProcessEvents(event_node *firstEvent, configuration_info *configInfo){

  event_node *curEvent = firstEvent;
  while(curEvent != NULL){

    //if the event spans two work days then process accordingly
    if(eventSpansTwoDays(curEvent,configInfo)){
      splitEvent(curEvent,configInfo);
    }
    //fill in the time information
    addTimeString(curEvent, configInfo->twentyFourHourTime);

    //truncate the event if it needs to be truncated
    truncateTime(curEvent, configInfo);
    //fill in font info
    setFonts(curEvent, configInfo);

    //fill in color information
    setColors(curEvent, configInfo);
    applyRules(curEvent, configInfo);
    curEvent = curEvent->next_event;
  }
}
