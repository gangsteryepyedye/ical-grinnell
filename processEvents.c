#include "processEvents.h"


int isEventInWeek(icalcomponent * event, icaltime_span weekSpan){
  struct icaltime_span eventSpan;

  eventSpan = icalcomponent_get_span(event);
  
  return icaltime_span_overlaps(&eventSpan, &weekSpan);

}



event_node * createEventNode(icalcomponent *event){
  event_node *newEvent;
  icaltimetype start,end;
  time_t rawtime;
  struct tm *temp;
  time(&rawtime);
  newEvent = (event_node *) malloc(1 * sizeof(event_node));
  newEvent->st = (struct tm *) malloc(1 * sizeof(struct tm));
  newEvent->et = (struct tm *) malloc(1 * sizeof(struct tm));
  newEvent->summary = (char *) malloc(31 * sizeof(char));
  newEvent->location = (char *) malloc(31 * sizeof(char));
  newEvent->timeString = (char *) malloc(31 * sizeof(char));
  newEvent->options = (node_options *) malloc(1 * sizeof(node_options));
  start = icalcomponent_get_dtstart(event);
  end = icalcomponent_get_dtend(event);

  //I do not have a complete understanding of tm structure stuff
  //but this makes it work, should look at this more
  temp = localtime(&rawtime);
  memcpy(newEvent->st,temp, sizeof(struct tm));
  memcpy(newEvent->et,temp, sizeof(struct tm));
  
  newEvent->st->tm_sec = start.second;
  newEvent->st->tm_min = start.minute;
  newEvent->st->tm_hour = start.hour;
  newEvent->st->tm_mday = start.day;
  newEvent->st->tm_mon = start.month -1;
  newEvent->st->tm_year = start.year - 1900;


  newEvent->et->tm_sec = end.second;
  newEvent->et->tm_min = end.minute;
  newEvent->et->tm_hour = end.hour;
  newEvent->et->tm_mday = end.day;
  newEvent->et->tm_mon = end.month -1;
  newEvent->et->tm_year = end.year - 1900;

  newEvent->start_time = mktime(newEvent->st);

  newEvent->end_time = mktime(newEvent->et);
  newEvent->next_event = NULL;
  strncpy(newEvent->summary, icalcomponent_get_summary(event), 30 * sizeof(char));
  strncpy(newEvent->location, icalcomponent_get_location(event), 30 * sizeof(char));  
  newEvent->summary[30] ='\0';
  newEvent->location[30] ='\0';


  return newEvent;
}

//THIS NEEDS TO BE TESTED MORE, right now everything always passes the first IF 
//but this might not always be true
void insertNode(event_node **currentNode, event_node **firstNode, event_node **lastNode){
  event_node *cn;

  if(difftime((*currentNode)->start_time,(*lastNode)->start_time) >= 0){
    (*lastNode)->next_event = *currentNode;
    *lastNode = *currentNode;
  }

  // otherwise check to see if it is before firstNode
  else if(difftime((*firstNode)->start_time, (*currentNode)->start_time) > 0){
    //if it is then put it in front and update accordingly
    (*currentNode)->next_event = *firstNode;
    firstNode = currentNode;
  }
  else{
    cn = *firstNode;
    //as long as the event after cn is before currentNode, go to next node
    while(difftime(cn->next_event->start_time, (*currentNode)->start_time) < 0){
      cn = cn->next_event;
    }
    (*currentNode)->next_event = cn->next_event;
    cn->next_event = *currentNode;
  }
}
      

//the events calendar must all be within the week that is desired, this goes through and
//creates a linked list of all of the events. 
event_node * createLinkedListOfEvents(icalcomponent *calendar, icaltime_span weekSpan){
  icalcomponent * currentEvent; 
  
  event_node *currentNode, *firstNode, *lastNode;
  firstNode = NULL;
  lastNode = NULL;
  currentEvent = icalcomponent_get_first_real_component(calendar); 

  while(currentEvent != 0){
    if(isEventInWeek(currentEvent, weekSpan)){
      currentNode = createEventNode(currentEvent);
      if(firstNode == NULL){
        firstNode = currentNode;
        lastNode = currentNode;
        currentNode->next_event = currentNode;
      }
      else{
        insertNode(&currentNode, &firstNode, &lastNode);

      }
    }
    // icalcomponent_free(currentEvent);
    currentEvent = icalcomponent_get_next_component(calendar,ICAL_VEVENT_COMPONENT);

  }
  //icalcomponent_free(calendar);
  return firstNode;
}

void assignEventsToDays(work_week *week, event_node *firstEvent){
  int previousDay,currentDay;
  event_node *currentEvent, *previousEvent;
  currentEvent= firstEvent;
  currentDay = currentEvent->st->tm_wday;
  week->day[currentDay]->first_event = currentEvent;
  previousDay = currentDay;
  previousEvent = currentEvent;
  while(currentEvent->next_event != NULL){
    //if the next event is not in the same day then it must be the first event
    //of that day, so have the array of days have that be the first event of that day
    currentDay = currentEvent->st->tm_wday;
    if(currentDay != previousDay){
      //first wrap up the previous days list of events
      previousEvent->next_event = NULL;
      week->day[currentDay]->first_event = currentEvent;
    }
    previousDay = currentDay;
    previousEvent = currentEvent;
    currentEvent = currentEvent->next_event;
  }

}  
 

