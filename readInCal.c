#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <libical/ical.h>
#include "readInCal.h"


//from usingLibical.txt
char* read_stream(char *s, size_t size, void *d){ 
  char *c = fgets(s,size, (FILE*)d);
  return c;
}



//create internal representation by using icalparser_parse
icalcomponent * parseFile(char * fileName){
  icalcomponent *cal;

  icalparser *parser = icalparser_new();
  FILE* stream = fopen(fileName,"r");
  icalparser_set_gen_data(parser,stream);

  cal = icalparser_parse(parser,&read_stream);

  
  fclose(stream);
  icalparser_free(parser);
  return cal;
}
