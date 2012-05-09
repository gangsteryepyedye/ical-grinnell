#ifndef CAL_SYSTEM_PRINT_FUNCTIONS_H
#define CAL_SYSTEM_PRINT_FUNCTIONS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "dataStructures.h"
#include "calEnum.h"



char * substr(char* str, int start, int length);

void fprintTimes(FILE* html);

void fprintWeekDay(int d,FILE* html);

void printEventNode(event_node *event,FILE* html);

void printEmptyEventNode(FILE* html);

void printColor(enum color c);

void printFont(enum font c);

void printEvents(event_node *firstEvent,FILE* html);


void printConfigurationInfo(configuration_info * configInfo);
void printWeekDay(enum day_of_week d);


FILE* printHeader();

#endif