
#include "printFunctions.h"
#include "calEnum.h"
#include <string.h> 

void printEventNode(event_node *event, FILE* html){
  fprintf(html,"<li style='background-color:rgb(227,227,255);border-color:#A9ABFE;color:#333;'>");


  fprintf(html,"%s\n", event->summary);
  fprintf(html,"<br>");
  fprintf(html,"\tLocation: %s\n", event->location);
  //the +1 adjusts the month since it is stored as 0-11 not 1-12
  fprintf(html,"<br>");
  fprintf(html,"\tDate: %d/%d\n", event->st->tm_mon + 1, event->st->tm_mday);
  fprintf(html,"<br>");
  fprintf(html,"\tTime: %s\n", event->timeString);
  //fprintf(html,"\tBox Color: ");
  //printColor(event->options->box_color);
  fprintf(html,"\n");

  //fprintf(html,"\tTime font: ");
  //printFont(event->options->time_font);
  fprintf(html,"\n");
  fprintf(html,"</li>");
  fprintf(html,"<br>");
}

void fprintTimes(FILE* html){

    fprintf(html,"<li style='margin-bottom:60px;border-top:1px dotted rgb(221, 221, 221);margin-top:30px;'>7am</li>");
    fprintf(html,"<li style='margin-bottom:60px;border-top:1px dotted rgb(221, 221, 221);'>8am</li>");
    fprintf(html,"<li style='margin-bottom:60px;border-top:1px dotted rgb(221, 221, 221);'>9am</li>");  
    fprintf(html,"<li style='margin-bottom:60px;border-top:1px dotted rgb(221, 221, 221);'>10am</li>");
    fprintf(html,"<li style='margin-bottom:60px;border-top:1px dotted rgb(221, 221, 221);'>11am</li>");
    fprintf(html,"<li style='margin-bottom:60px;border-top:1px dotted rgb(221, 221, 221);'>12pm</li>");
    fprintf(html,"<li style='margin-bottom:60px;border-top:1px dotted rgb(221, 221, 221);'>1pm</li>");
    fprintf(html,"<li style='margin-bottom:60px;border-top:1px dotted rgb(221, 221, 221);'>2pm</li>");
    fprintf(html,"<li style='margin-bottom:60px;border-top:1px dotted rgb(221, 221, 221);'>3pm</li>");
    fprintf(html,"<li style='margin-bottom:60px;border-top:1px dotted rgb(221, 221, 221);'>4pm</li>");
    fprintf(html,"<li style='margin-bottom:60px;border-top:1px dotted rgb(221, 221, 221);'>5pm</li>");
    
  

}

void printEmptyEventNode(FILE* html){
    fprintf(html,"<li style='margin-bottom:60px;border-bottom:1px dotted rgb(221, 221, 221);'><br></li>");
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

void fprintWeekDay(int d,FILE* html){
  

  switch (d)
    {
    case 0:
      fprintf(html,"<li>Sunday</li>");
      break;
    case 1:
      fprintf(html,"<li>Monday</li>");
      break;
    case 2:
      fprintf(html,"<li>Tuesday</li>");
      break;
    case 3:
      fprintf(html,"<li>Wednesday</li>");
      break;
    case 4:
      fprintf(html,"<li>Thursday</li>");
      break;
    case 5:
      fprintf(html,"<li>Friday</li>");
      break;
    case 6:
      fprintf(html,"<li>Saturday</li>");
      break;
    default:
      printf("Unknown");
    }



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

void printEvents(event_node *firstEvent,FILE* html){
  event_node *currentEvent = firstEvent;
  char* timeArray[11]={"7:","8:","9:","10:","11:","12:","1:","2:","3:","4:","5:"};
  int counter=0;
  int i;
  if(firstEvent==NULL){
    for(i=0;i<11;i++){
      printEmptyEventNode(html);
    }
  }

  while(currentEvent != NULL){
    
    char* temp=(char*)malloc(10);
    
    temp=substr(currentEvent->timeString,0,4);
    //printf("Temp: %s",temp);
    //printf("Time: %s\n",time[counter]);

    if(temp[0]==timeArray[counter][0]&&temp[1]==timeArray[counter][1]){

      printEventNode(currentEvent,html);
      counter++;
      currentEvent = currentEvent->next_event;
    }
    else{

      printEmptyEventNode(html);
      counter++;
    }

  }
  
  if(counter>0){
    int j;
    for(j=(11-counter);j>1;j--){
      printEmptyEventNode(html);
    }
  }



}

char * substr(char* str, int start, int length) {
    char *newString = (char *)malloc(length * sizeof(char));
    int i, x = 0;
    int end=start+length;
    for(i = start ; i <= end; i++)
        newString[x++] = str[i];
    newString[x] = '\0';
    return newString;
}
