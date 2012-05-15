/** @file
    @brief
    
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "dataStructures.h"
#include "calEnum.h"

int weekDayToInt(char * weekDayString){
  if(! strncmp(weekDayString, "SUNDAY",6)){
    return SUNDAY;
  }
  else if(! strncmp(weekDayString, "MONDAY",6)){
    return MONDAY;
  }
  else if(! strncmp(weekDayString, "TUESDAY",7)){
    return TUESDAY;
  }
  else if(! strncmp(weekDayString, "WEDNESDAY",9)){
    return WEDNESDAY;
  }
  else if(! strncmp(weekDayString, "THURSDAY",8)){
    return THURSDAY;
  }
  else if(! strncmp(weekDayString, "FRIDAY",6)){
    return FRIDAY;
  }
  else if(! strncmp(weekDayString, "SATURDAY",8)){
    return SATURDAY;
  }

  printf("The day %s is not known, setting day to MONDAY\n", weekDayString);
  return MONDAY;
}



int colorStringToInt(char * colorString){
  if(! strncmp(colorString, "CLEAR",5)){
    return CLEAR;
  }
  else if(! strncmp(colorString, "RED",3)){
    return RED;
  }
  else if(! strncmp(colorString, "ORANGE",6)){
    return ORANGE;
  }
  else if(! strncmp(colorString, "YELLOW",6)){
    return YELLOW;
  }
  else if(! strncmp(colorString, "GREEN",5)){
    return GREEN;
  }
  else if(! strncmp(colorString, "BLUE",4)){
    return BLUE;
  }
  else if(! strncmp(colorString, "PURPLE",6)){
    return PURPLE;
  }
  else if(! strncmp(colorString, "BLACK",5)){
    return BLACK;
  }
  printf("The color %s is not known, setting color to BLACK\n", colorString);
  return 7;
}



int fontStringToInt(char *fontString){
  if(! strncmp(fontString, "FONT_A", 6)){
    return FONT_A;
  }
  else if(! strncmp(fontString, "FONT_B", 6)){
      return FONT_B;
  }
  
  printf("The font %s is not known, setting font to FONT_A\n", fontString);
  return 0;
}

int rafStringToInt(char * rafString){
  if(!strcmp(rafString, "SUMMARY")){
    return SUMMARY;
  }
  else if(! strcmp(rafString, "LOCATION")){
    return LOCATION;
  }
  else if(! strcmp(rafString, "TIME")){
    return TIME;
  }
  return SUMMARY;
}

int rcfStringToInt(char * rcfString){
  if(! strcmp(rcfString, "BOX_COLOR")){
    return BOX_COLOR;
  }
  else if(!strcmp(rcfString, "TEST_COLOR")){
    return TEXT_COLOR;
  }
  else if(! strcmp(rcfString, "TIME_FONT")){
    return TIME_FONT;
  }
  else if(! strcmp(rcfString, "SUMMARY_FONT")){
    return SUMMARY_FONT;
  }
  else if(! strcmp(rcfString, "LOCATION_FONT")){
    return LOCATION_FONT;
  }
  
  return BOX_COLOR;
}
  
