#ifndef CAL_SYSTEM_PRINT_FUNCTIONS_H
#define CAL_SYSTEM_PRINT_FUNCTIONS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "dataStructures.h"
#include "calEnum.h"
void printEventNode(event_node *event);

void printColor(enum color c);

void printFont(enum font c);

void printEvents(event_node *firstEvent);


void printConfigurationInfo(configuration_info * configInfo);
void printWeekDay(enum day_of_week d);


#endif
