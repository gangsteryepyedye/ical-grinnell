

#include "readConfigFile.h"
#include "enumFunctions.h"
#include <string.h>

//All of the process___ functions take a line of text and sets the 
//appropriate values in the configInfo structure, I have better things
//to do than write up comments for all of them. 
void processStartOfDay(char *line, configuration_info *configInfo){
  sscanf(line, "%*s = %d:%d",&(configInfo->startOfDayHour),&(configInfo->startOfDayMinute));
}

void processEndOfDay(char *line, configuration_info *configInfo){
  sscanf(line, "%*s = %d:%d",&(configInfo->endOfDayHour),&(configInfo->endOfDayMinute));
}

void processFirstDay(char *line, configuration_info * configInfo){
  char *tmp;
  tmp = malloc(20 * sizeof(char));
  sscanf(line, "%*s = %s",tmp);
  configInfo->firstDayOfWeek = weekDayToInt(tmp);
  free(tmp);
}

void processLastDay(char *line, configuration_info * configInfo){
  char *tmp;
  tmp = malloc(20 * sizeof(char));
  sscanf(line, "%*s = %s",tmp);
  configInfo->lastDayOfWeek = weekDayToInt(tmp);
  free(tmp);
}

void processTimeFont(char* line, configuration_info * configInfo){
  char *tmp;
  tmp = malloc(20 * sizeof(char));
  sscanf(line, "%*s = %s",tmp);
  configInfo->timeFont= fontStringToInt(tmp);
  free(tmp);
}

void processSummaryFont(char* line, configuration_info * configInfo){
  char *tmp;
  tmp = malloc(20 * sizeof(char));
  sscanf(line, "%*s = %s",tmp);
  configInfo->summaryFont= fontStringToInt(tmp);
  free(tmp);
}

void processLocationFont(char* line, configuration_info * configInfo){
  char *tmp;
  tmp = malloc(20 * sizeof(char));
  sscanf(line, "%*s = %s",tmp);
  configInfo->locationFont= fontStringToInt(tmp);
  free(tmp);
}

void processDefaultFontColor(char* line, configuration_info * configInfo){
  char *tmp;
  tmp = malloc(20 * sizeof(char));
  sscanf(line, "%*s = %s",tmp);
  configInfo->defaultFontColor = colorStringToInt(tmp);
  free(tmp);
}

void processDefaultBoxColor(char* line, configuration_info * configInfo){
  char *tmp;
  tmp = malloc(20 * sizeof(char));
  sscanf(line, "%*s = %s",tmp);
  configInfo->defaultBoxColor = colorStringToInt(tmp);
  free(tmp);
}

void processNameOfOutputFile(char* line, configuration_info * configInfo){
  char *tmp;
  tmp = malloc(100 * sizeof(char));
  sscanf(line, "%*s = %s",tmp);
  configInfo->nameOfOutputFile = tmp;

}

void processTwentyFourHourFlag(char* line, configuration_info * configInfo){
  char *tmp;
  tmp = malloc(20 * sizeof(char));
  sscanf(line, "%*s = %s",tmp);
  if(!strncmp(tmp, "FALSE", 5)){
    configInfo->twentyFourHourTime = false;
  }
  else{
    configInfo->twentyFourHourTime = true;
  }    
  free(tmp);
}
//Rule SUMMARY = Office hour : BOXCOLOR = RED
void processRule(char * line, configuration_info *configInfo){
  char *antecedentField, *antecedentValue, *consequentField, *consequentValue;
  ruleNode *rule;
  rule = malloc(1 * sizeof(ruleNode));
  antecedentField = malloc(100 * sizeof(char));
  antecedentValue = malloc(100 * sizeof(char));
  consequentField = malloc(100 * sizeof(char));
  consequentValue = malloc(100 * sizeof(char));
 

  //printf("INPUT %s\n", line);
  sscanf(line,"%*s %s = \"%[a-zA-Z0-9 ]\" : %s = %s",antecedentField, antecedentValue, consequentField, consequentValue);
  /* printf("af: %s\n", antecedentField); */
  /* printf("av: %s\n", antecedentValue); */
  /* printf("cf: %s\n", consequentField); */
  /* printf("cv: %s\n", consequentValue); */
  rule->raf = rafStringToInt(antecedentField);
  rule->rcf = rcfStringToInt(consequentField);
  rule->antecedentValue = antecedentValue;
  rule->consequentValue = consequentValue;
  if(configInfo->rules != NULL){
    rule->nextRule = configInfo->rules;
  }
  configInfo->rules = rule;

  /* free(antecedentField); */
  /* free(consequentField); */
  
}

/** @brief
    The @c processConfigFileLine function determines the field in being read
    and then assigns it the specified value
*/

void processConfigFileLine(char *line, configuration_info * configInfo){
  if(! strncmp(line,"START_OF_DAY",12)){
    processStartOfDay(line, configInfo);
  }
  else if(! strncmp(line, "END_OF_DAY", 10)){
    processEndOfDay(line, configInfo);
  }
  else if(! strncmp(line, "FIRST_DAY", 9)){
    processFirstDay(line, configInfo);
  }
  else if(! strncmp(line, "LAST_DAY", 8)){
    processLastDay(line, configInfo);
  }
  else if(! strncmp(line, "OUTPUT_FILE", 10)){
    processNameOfOutputFile(line, configInfo);
  }
  else if(! strncmp(line, "TIME_FONT", 9)){
    processTimeFont(line, configInfo);
  }
  else if(! strncmp(line, "SUMMARY_FONT", 12)){
    processSummaryFont(line, configInfo);
  }
  else if(! strncmp(line, "LOCATION_FONT", 13)){
    processLocationFont(line, configInfo);
  }
  else if(! strncmp(line, "BOX_COLOR", 9)){
    processDefaultBoxColor(line, configInfo);
  }
  else if(! strncmp(line, "FONT_COLOR", 10)){
    processDefaultFontColor(line, configInfo);
  }
  else if(! strncmp(line, "TWENTY_FOUR_HOUR", 16)){
    processTwentyFourHourFlag(line, configInfo);
  }
  else if(! strncmp(line, "Rule", 4)){
     processRule(line, configInfo);
  }
  else{
    printf("Could not process the string: %s\n", line);
  }

}
/** @brief
    The @c readConfigFile function reads the file icalConfig and 
    fills in the configuration_info data structure

    @remark
    The heart of this function is just a while loop that reads in a line, and then
    sends that line to a processing function. I had considered making the format of the
    configuration file more rigid, which would enable us to just have a series of fscanf
    statements. However I decided that this would be too rigid, so I made it so that 
    the fields could come in any order in the config file. This leads to some ugliness
    later on, since it is necesary to do 
*/
configuration_info * readConfigFile(){
  configuration_info *configInfo;
  configInfo = (configuration_info *) malloc(1 * sizeof(configuration_info));
  char *tmp;
  tmp = malloc(500*sizeof(char));
  FILE *fp;
  fp = fopen("icalConfig", "r");
  /*As long as there is more text we send it to the processConfigFileLine, which 
    processes a line, and sets the appropriate field. */
  while(fgets(tmp, 100, fp) != NULL){
    processConfigFileLine(tmp, configInfo);
  }
  return configInfo;
}



