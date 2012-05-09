#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <libical/ical.h>

#include "calSystem.h"
#include "readConfigFile.h"







int main(int argc, char** argv){
  work_week *week;
  configuration_info *configInfo;
  FILE* html;
  configInfo = readConfigFile();
  setStartDate(configInfo,4,23,2012);
  //printConfigurationInfo(configInfo);
  // printf("%s\n",configInfo->nameOfOutputFile);
  week = createWorkWeekFromFile("academic.ics", configInfo);

  createPrintableFile(week, configInfo);
  html = printHeader();
  int i;
  for(i = -1; i < 7;i++){
    fprintf(html,"<ul style='float:left;list-style-type:none;border-right:1px solid rgb(221, 221, 221);font-size:12px;min-width:150px;min-height:1080px;padding-left:5px;padding-right:5px;'>");
    if(i==-1){
      fprintTimes(html);
    }
    else{
      fprintWeekDay(i,html);
      printEvents(week->day[i]->first_event,html);
    }
    fprintf(html,"</ul>");
  }
    cleanup(week, configInfo);
  return 0;
} 



FILE* printHeader(){

    FILE *html = fopen("events.html", "w"); 
    fprintf(html,"Content-Type: text/html\n\n");
    fprintf(html,"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 5.0//EN\">\n\n");
    fprintf(html,"<HTML>\n\n");
    fprintf(html,"<HEAD>\n");
    fprintf(html,"    <TITLE>ICal Output</TITLE>\n");
    fprintf(html,"</HEAD>\n\n");
    fprintf(html,"<BODY>\n\n");

    fprintf(html,"<H1>Events</H1>\n\n");  
    
    return html;
}
