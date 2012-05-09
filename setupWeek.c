#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <libical/ical.h>
#include "dataStructures.h"
#include "setupWeek.h"

//the weekspan is used in doing the first pass of filtering,
struct icaltime_span createWeekSpan(configuration_info *configInfo){

  struct icaltimetype weekStart, weekEnd;
  struct icaltime_span weekSpan;
  char startString[100], endString[100];
  sprintf(startString,"%d-%2d-%2dT00:00:00",configInfo->startYear, configInfo->startMonth, configInfo->startMDay);
  sprintf(endString,"%d-%2d-%2dT23:59:59", configInfo->endYear,configInfo->endMonth,configInfo->endMDay);
 //NEEDS TO BE CHANGED TO BE MORE FLEXIBLE, CAN DO LATER
  icaltimezone *curzone = icaltimezone_get_builtin_timezone("America/Chicago");
  weekStart =icaltime_from_string(startString);
  weekEnd = icaltime_from_string(endString);
  weekStart.zone = curzone;
  weekEnd.zone = curzone;
  weekSpan = icaltime_span_new(weekStart, weekEnd, 0);//0 = not busy
  return weekSpan;
}



work_week* createWorkWeek(configuration_info *configInfo){
  work_week *week = (work_week *) malloc( 1 * sizeof(work_week));
  week->startOfDayHour = configInfo->startOfDayHour;
  week->startOfDayMinute = configInfo->startOfDayMinute;
  week->endOfDayHour = configInfo->endOfDayHour;
  week->endOfDayMinute = configInfo->endOfDayMinute;
  int i;
  for(i = 0; i <7;i++){
    week->day[i] = (work_day *) malloc(1 * sizeof(work_day));
  }

  week->firstDay = configInfo->firstDayOfWeek;
  week->lastDay = configInfo->lastDayOfWeek;
  return week;

}
