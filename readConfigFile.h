/** @file
   @brief  The functions that are used to read a configuration file and 
   use it to fill in the in configuration_info data structure

   @details The most important funciton is readConfigFile. It opens up the configuration file
   name icalConfig. It then the file line by line, and sends each line to the 
   @c processConfigFileLile function. There are many different functions called
   process_______ that are all quite similar, however I have not included documentation for them
   because there are more important things to do.

   @remark 
    @remark
    I had considered making the format of the configuration file more rigid, which would 
    have enabled us to just have a series of calls to fscanf statements. However I decided
    that this would be too rigid, so I made it so that the fields could come in any order
    in the config file. This however leads to a large if..else if..else if ... ... else 
    where we check which field is described in the line based upon strncmp.
*/

#ifndef CAL_SYSTEM_READ_CONFIG_H
#define CAL_SYSTEM_READ_CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <libical/ical.h>
#include "dataStructures.h"


/** @brief
    The @c processConfigFileLine processes one line of the configuration 
    file for the ical printable schedule system. 

    @param line a line of text from the configuration file
    @param configInfo the structure into which the configuration options
    will be stored
*/
void processConfigFileLine(char *line, configuration_info * configInfo);


/** @brief
    The @c readConfigFile function reads the file icalConfig and 
    fills in the configuration_info data structure

    @remark
    Currently I have the value for the file that is oppened hard coded.
    If we have a chance we should change this so that it takes one argument
*/
configuration_info * readConfigFile();


#endif /* !CAL_SYSTEM_READ_CONFIG_H */
