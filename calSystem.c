/** @file
   @brief calSystem contains all of the highest level function

   @details
   In general one should call @c createConfiguration followed by @c createWorkWeekFromFile
   followd by @c createPrintableFile
  
*/
#include "calSystem.h"


/** @brief
    The @c createConfiguration function returns the configuration_info structure
    describing how to make the output, as well a what is the range of dates.

    @remark Currently this is simply a stub, it calls defaulCOnfiguration.
*/
configuration_info *createConfiguration(){
  return defaultConfiguration(2,27,2012);
}

void setStartDate(configuration_info * configInfo, int startMonth, int startMDay, int startYear){
  configInfo->startMonth = startMonth;
  configInfo->startMDay = startMDay;
  configInfo->startYear = startYear;
  
  configInfo->endMonth = startMonth;
  configInfo->endMDay = startMDay + 5;
  configInfo->endYear = startYear;
}

configuration_info * defaultConfiguration(int startMonth, int startMDay, int startYear){
  configuration_info *configInfo;
  configInfo = (configuration_info *) malloc(1 * sizeof(configuration_info));
  configInfo->startOfDayHour = 7;
  configInfo->startOfDayMinute = 0;
  configInfo->endOfDayHour = 17;
  configInfo->endOfDayMinute = 0;
  
  configInfo->firstDayOfWeek = MONDAY;
  configInfo->lastDayOfWeek = FRIDAY;
  
  configInfo->startMonth = startMonth;
  configInfo->startMDay = startMDay;
  configInfo->startYear = startYear;
  
  configInfo->endMonth = startMonth;
  configInfo->endMDay = startMDay + 5;
  configInfo->endYear = startYear;

  configInfo->twentyFourHourTime = false;
  configInfo->nameOfOutputFile = "OutputFile";
  return configInfo;
}


work_week * createWorkWeekFromFile(char * calendarFile, configuration_info *configInfo){
  icalcomponent *calendar;
  icaltime_span weekSpan;
  event_node *firstEvent;
  work_week *week;
  week = createWorkWeek(configInfo);
  weekSpan = createWeekSpan(configInfo);

  //after this step the calendarFile should never be read again
  calendar = parseFile(calendarFile);
  
  //after this step libical should no longer be used
  firstEvent = createLinkedListOfEvents(calendar, weekSpan);

  //at this point the only events remaining should overlap with the work week
  //after this step the events should not be modified expect in the process that assigns them to days  
  postProcessEvents(firstEvent,configInfo);


  assignEventsToDays(week,firstEvent);

  return week;
}

void freeEvent(event_node *event){
  free(event->st);
  free(event->et);
  free(event->summary);
  free(event->location);
  free(event->timeString);
  free(event->options);
}

void freeDay(work_day *day){
  event_node *curEvent,*nextEvent;
  curEvent = day->first_event;
  while(curEvent != NULL){
    nextEvent = curEvent->next_event;
    freeEvent(curEvent);
    free(curEvent);
    curEvent = nextEvent;
  }
}

void freeWeek(work_week *week){
  int i;
  for(i = 0; i <7; i++){
    if(week->day[i]){
      freeDay(week->day[i]);
    }
    free(week->day[i]);
  }
  free(week);
}

void freeRules(ruleNode *rules){
  ruleNode *curRule, *nextRule;
  curRule = rules;
  while(curRule != NULL){
    nextRule = curRule->nextRule;
    free(curRule->antecedentValue);
    free(curRule->consequentValue);
    free(curRule);
    curRule = nextRule;
  }
}

void freeConfig(configuration_info *configInfo){
  if(configInfo->rules){
    freeRules(configInfo->rules);
  }
  //free(configInfo->nameOfOutputFile);
  free(configInfo);
}
void cleanup(work_week *week, configuration_info *configInfo){
  freeWeek(week);
  freeConfig(configInfo);
}

//STUB
void  createPrintableFile(work_week *week,configuration_info *configInfo){

}
