/** @file
   @brief calSystem contains all of the highest level function

   @details
   In general one should call @c createConfiguration followed by @c createWorkWeekFromFile
   followd by @c createPrintableFile
  
*/
#ifndef CAL_SYSTEM_H
#define CAL_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <libical/ical.h>

#include "readInCal.h"
#include "dataStructures.h"
#include "setupWeek.h"
#include "processEvents.h"
#include "postProcessEvents.h"
#include "printFunctions.h"

/** @brief
    The @c createConfiguration function returns the configuration_info structure
    describing how to make the output, as well a what is the range of dates.

    @remark Currently this is simply a stub, it calls defaulCOnfiguration.
*/
    
configuration_info * createConfiguration();


void setStartDate(configuration_info * configInfo, int startMonth, int startMDay, int startYear);

//simply creates a configuration structure that has its information 
//filled in, default is work week is Monday-Friday, 7:00am-5:00pm

/** @brief
    The @c defaultConfiguration function returns a configuration_info structure
    describing a "standard" work week. 

    @remark
    The configuration is for a Monday-Friday work week with each work day lasting from
    7:00 am to 5:00 pm. And the printable file will be called OutputFile

    @param startMonth the month in which the desired work week begins
    @param startMDay the day of the month on which the desired work week begins.
    @param startYear the year in which the desired work week begins
*/
configuration_info * defaultConfiguration(int startMonth, int startMDay, int startYear);


//given the name of a .ics file and a pointer a configuration_info structure
//this will return a pointer to a work_week structure.
//I envision that after this is called we call something like
// makePrintableCalendar(week, configInfo)
//Where "week" is the value returned by this function

/** @brief
    The @c createWorkWeekFromFile function processes the calendarFile based upon the information
    in @c configInfo to create @work_week that can then be used to create a printable file

    @param calendarFile the name of a valid .ics file
    @param configInfo configuration_info structure describing which events to include, and
    how they should be configured

*/
work_week * createWorkWeekFromFile(char * calendarFile, configuration_info *configInfo);


void cleanup(work_week *week, configuration_info *configInfo);

/** @brief
    The @c createPrintableFile creates a file that can be printed, based on the information
    in @c week and @c configInfo

    @param week The week for which you want a printable file
    @param configInfo the configuration information describing how to make the printable file

    @remark
    @c configInfo should be the the structure that was passed into @c createWorkWeekFromFile.
    This function is currently just a stub.
*/
void  createPrintableFile(work_week *week,configuration_info *configInfo);
#endif
