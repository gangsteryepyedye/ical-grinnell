
OBJS = calSystem.o readInCal.o setupWeek.o \
 processEvents.o postProcessEvents.o \
 printFunctions.o readConfigFile.o \
 enumFunctions.o
CC = gcc
CFLAGS = -Wall -c -g $(DEBUG)
LFLAGS = -Wall -g  $(DEBUG) -lical

calSys : $(OBJS) main.c
	$(CC) $(LFLAGS) main.c $(OBJS) -o calSys

calSystem.o : calSystem.c calSystem.h
	$(CC) $(CFLAGS) calSystem.c

readInCal.o : readInCal.c readInCal.h dataStructures.h
	$(CC) $(CFLAGS) readInCal.c

setupWeek.o : setupWeek.c setupWeek.h dataStructures.h
	$(CC) $(CFLAGS) setupWeek.c

processEvents.o : processEvents.c processEvents.h dataStructures.h
	$(CC) $(CFLAGS) processEvents.c

readConfigFile.o : readConfigFile.c readConfigFile.h dataStructures.h
	$(CC) $(CFLAGS) readConfigFile.c

printFunctions.o : printFunctions.c printFunctions.h
	$(CC) $(CFLAGS) printFunctions.c

enumFunctions.o : enumFunctions.c enumFunctions.h
	$(CC) $(CFLAGS) enumFunctions.c

clean:
	\rm *.o *~ calSys
