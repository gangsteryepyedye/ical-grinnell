
#include "printFunctions.h"
#include "calEnum.h"
void printEventNode(event_node *event){
  printf("%s\n", event->summary);
  printf("\tLocation: %s\n", event->location);
  //the +1 adjusts the month since it is stored as 0-11 not 1-12
  printf("\tDate: %d/%d\n", event->st->tm_mon + 1, event->st->tm_mday);
  printf("\tTime: %s\n", event->timeString);
  printf("\tBox Color: ");
  printColor(event->options->box_color);
  printf("\n");

  printf("\tTime font: ");
  printFont(event->options->time_font);
  printf("\n");
}
void printConfigurationInfo(configuration_info * configInfo){

  printf("The output will be in the file: %s\n", configInfo->nameOfOutputFile);
  printf("Start time: %d:%02d\n", configInfo->startOfDayHour, configInfo->startOfDayMinute);
  printf("End time: %d:%02d\n", configInfo->endOfDayHour, configInfo->endOfDayMinute);
  printf("Work week starts on: ");
  printWeekDay(configInfo->firstDayOfWeek);
  printf("\n");
  printf("Work week ends on: ");
  printWeekDay(configInfo->lastDayOfWeek);
  printf("\n");
  printf("Time font: ");
  printFont(configInfo->timeFont);
  printf("\n");
  printf("Location font: ");
  printFont(configInfo->locationFont);
  printf("\n");
  printf("Summary font: ");
  printFont(configInfo->summaryFont);
  printf("\n");
  printf("Default font color: ");
  printColor(configInfo->defaultFontColor);
  printf("\n");
  printf("Default box color: ");
  printColor(configInfo->defaultBoxColor);
  printf("\n");
}


void printWeekDay(enum day_of_week d){
  switch (d)
    {
    case MONDAY:
      printf("Monday");
      break;
    case TUESDAY:
      printf("Tuesday");
      break;
    case WEDNESDAY:
      printf("Wednesday");
      break;
    case THURSDAY:
      printf("Thursday");
      break;
    case FRIDAY:
      printf("Friday");
      break;
    case SATURDAY:
      printf("Saturday");
      break;
    case SUNDAY:
      printf("Sunday");
      break;
    default:
      printf("Unknown");
    }
}

void printColor(enum color c){
  switch (c)
    {
    case CLEAR:
      printf("Clear");
      break;
    case RED:
      printf("Red");
      break;
    case ORANGE:
      printf("Orange");
      break;
    case YELLOW:
      printf("Yellow");
      break;
    case GREEN:
      printf("Green");
      break;
    case BLUE:
      printf("Blue");
      break;
    case PURPLE:
      printf("Purple");
      break;
    case BLACK:
      printf("Black");
      break;
    default:
      printf("Unknown");
    }
}
void printFont(enum font c){
  switch (c)
    {
    case FONT_A:
      printf("Font A");
      break;
    case FONT_B:
      printf("Font B");
      break;
    default:
      printf("Unknown");
    }
}

void printEvents(event_node *firstEvent){
  event_node *currentEvent = firstEvent;
  while(currentEvent != NULL){
    printEventNode(currentEvent);
    currentEvent = currentEvent->next_event;
  }
}
