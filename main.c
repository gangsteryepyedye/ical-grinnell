#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <libical/ical.h>

#include "calSystem.h"
#include "readConfigFile.h"







int main(int argc, char** argv){
  work_week *week;
  configuration_info *configInfo;
  configInfo = readConfigFile();
  setStartDate(configInfo,5,7,2012);
  //printConfigurationInfo(configInfo);
  // printf("%s\n",configInfo->nameOfOutputFile);
  week = createWorkWeekFromFile("basic.ics", configInfo);

  createPrintableFile(week, configInfo);
  int i;
  for(i = 0; i < 7;i++){
    printf("DAY: %d\n", i);
    printEvents(week->day[i]->first_event);
  }
    cleanup(week, configInfo);
  return 0;
} 
