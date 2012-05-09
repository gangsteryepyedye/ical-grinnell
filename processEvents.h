/** @file
   @brief processEvents contains the functions used to process the events in an 
   iCal file and assign them to the proper days
*/

#ifndef CAL_SYSTEM_PROCESS_EVENT_H
#define CAL_SYSTEM_PROCESS_EVENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <libical/ical.h>

#include "dataStructures.h"
#include "processEvents.h"



//takes an icalcomponent and an icaltime_span
//prerequisites: icalcomponent must succsesfully return and event span
/** @brief
    The @c isEventInWeek determines if an event occurs in a given week
    @param event an icalcomponent
    @param weekSPan an icaltime_span for the desired week

    @return 1 if event overlaps with weekSpan, otherwise returns 0
*/
int isEventInWeek(icalcomponent * event, icaltime_span weekSpan);

/*based upon and icalcomponent this creates an event_node. It allocates 
  the memory that is need, ie for strings, and for the options structure.
  It also fills in as much information for the node that it can. 
  After an icalcomponent is processed by createEventNode the icalcomponent
  should never need to be accessed again. 
*/

/** @brief
    The @c createEventNode function Creates an event_node based upon an icalcomponent.

    @details
    This allocates the space needed to store information about an event, and fills in 
    as much information as it can. 

    @remark
    This function is a dividing line. Before this point libical is used to store
    the event information, and libical functions are used. After this function 
    all the information is stored in data structures that are defined in 
    dataStructures.h. 
*/
event_node * createEventNode(icalcomponent *event); 

/* this will insert currentNode into the proper place in the list where firstNode is
   the first node in a linked list of nodes. The expected case is that currentNode
   will be an event that happens after last node, and as such should become the new
   last node. insertNode really should never be called except by 
   createLinkedListOfEvents
   NOTE: The only case I have tested at all is the expected case
*/

/** @brief
    The @c insertNode function inserts an event_node into it proper place in a sorted
    linked list of event_nodes, based upon start time

    @param currentNode the node to be inserted
    @param firstNode the head of the linked list of event_nodes
    @param lastNode the last event_node in the linked list of event_nodes

    @remark
    I suspect that in most ics files the events are stored in order, so currentNode
    will be inserted afer lastNode
*/
void insertNode(event_node **currentNode, event_node **firstNode, event_node **lastNode);


//given an icalcomponent, which should be an ICAL_XROOT_COMPONENT
//it will construct a linked list of the events that overlap
//the span given as the second argument. The nodes of the list will be in order
//based on the start time of the events.
//A pointer to the first event will be returned. 

/** @brief
    The @c createLinkedListOfEvents function creates a linked list of all events
    that overlap the desired week. The list is sorted by start time of the event. 

    @param calendar the icalcomponent for the calendar on which to base a schedule
    @param weekSpan an icaltime_span defining the work week in interest

    @remark
    @c calendar should be the result of parseFile(calendarFile) 

    @return a pointer to the first event_node in the sorted linked list of all the events
    that overlap with the work week
*/
event_node * createLinkedListOfEvents(icalcomponent *calendar, icaltime_span weekSpan);


/*given a work_week and a pointer to an event_node assignEventsToDays
  will assign firstEvent, and and the events in the list to the proper
  day of the week.
  Preconditions:
  firstEvent is the first event in a linked list of events. The events must be sorted,
  furthermore all of the events must occur within 7 days of each other
  i.e. firstEvent should probably be the value returned from createLinkedListOfEvents
*/

/** @brief
    The @c assignEventsToDays function splits the events in a linked list into seperate linked lists
    with one linked list for each day where there are events

    @param week the structure that will keep track of the linked lists for each day
    @param firstEvent the first event_node in the linked list

*/
void assignEventsToDays(work_week *week, event_node *firstEvent);



#endif // ! CAL_SYSTEM_PROCESS_EVENT_H
