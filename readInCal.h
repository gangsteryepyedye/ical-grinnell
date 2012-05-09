

//from usingLibical.txt
char* read_stream(char *s, size_t size, void *d);


//will read an ics file and store in the format used in 
//libical.
icalcomponent * parseFile(char * fileName);
