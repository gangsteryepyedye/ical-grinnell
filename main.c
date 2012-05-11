#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <libical/ical.h>

#include "calSystem.h"
#include "readConfigFile.h"


void get_date( int * month, int * day, int * year ) {
    time_t timenow = time(0); 
    struct tm *current;


    current = localtime(&timenow);



return;
}


//
// given month, day, year, returns day of week, eg. Monday = 0 etc.
// tested for 1901 to 2099 (seems to work from 1800 on too)
// 
int weekday(int month, int day, int year)
{	
  int ix, tx, vx;

  switch (month) {
    case 2  :
	case 6  : vx = 0; break;
	case 8  : vx = 4; break;
	case 10 : vx = 8; break;
	case 9  :
	case 12 : vx = 12; break;
	case 3  :
	case 11 : vx = 16; break;
	case 1  :
	case 5  : vx = 20; break;
	case 4  :
	case 7  : vx = 24; break;
  }
  if (year > 1900)  // 1900 was not a leap year
    year -= 1900;
  ix = ((year - 21) % 28) + vx + (month > 2);  // take care of February 
  tx = (ix + (ix / 4)) % 7 + day;              // take care of leap year
  return (tx % 7);
}





int main(int argc, char** argv){
  work_week *week;
  configuration_info *configInfo;
  FILE* html;
  configInfo = readConfigFile();
  
  int* month=(int*)malloc(sizeof(int));
  int* day=(int*)malloc(sizeof(int));
  int* year=(int*)malloc(sizeof(int));

  //get_date(month,day,year);	
  //int monday = 11-weekday(5,11,2012);
  //printf("%d",monday);
  setStartDate(configInfo,5,6,2012);
  //printConfigurationInfo(configInfo);
  //printf("%s\n",configInfo->nameOfOutputFile);
  week = createWorkWeekFromFile("basic.ics", configInfo);

  createPrintableFile(week, configInfo);
  html = printHeader();
  int i;
  for(i = -1; i < 7;i++){
    fprintf(html,"<ul style='float:left;list-style-type:none;border-right:1px solid rgb(221, 221, 221);font-size:12px;min-width:150px;min-height:880px;padding-left:5px;padding-right:5px;'>");
    if(i==-1){
      fprintTimes(html);
    }
    else{
      fprintWeekDay(i,html);
      printf("Day %d \n", i);
      printEvents(week->day[i]->first_event,html);
    }
    fprintf(html,"</ul>");
  }
    cleanup(week, configInfo);
  return 0;
} 



FILE* printHeader(){

    FILE *html = fopen("events.html", "w"); 
    fprintf(html,"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 5.0//EN\">\n\n");
    fprintf(html,"<HTML>\n\n");
    fprintf(html,"<HEAD>\n");
    fprintf(html,"    <TITLE>ICal Output</TITLE>\n");
    fprintf(html,"</HEAD>\n\n");
    fprintf(html,"<BODY>\n\n");

    fprintf(html,"<H1>Events</H1>\n\n");  
    
    return html;
}
