/** @file
    @brief postProcessEvents contains the functions that are used to fill in information
    based upon confiuration information. It also has functions that modify the values stored in certain
    fields that will be used to display the events. Finally it contains the functions used for dealing
    with events that span multiple days. 

    @remark
    Many of these functions are  stubs that need to be filled in.

*/
#ifndef CAL_SYSTEM_POST_PROCESS_H
#define CAL_SYSTEM_POST_PROCESS_H


/** @brief
    The @eventSpansTwoDays determines if an event spans multiple 24 hour days
    
    @param event the event in question
    @param configInfo the configuration information being used
    @return true if the event spans two days, flase if not
*/
bool eventSpansTwoDays(event_node *event, configuration_info *configInfo);

/** @brief
    The @c splitEvent function splits an event that spans two (or more) days into
    two events

    @param event the event to be split
    @param configInfo the configuration information being used

    @details
    This will create one new event that will inserted into the linked list. 
    It should be identical to the orignial event, except that it will have its 
    st, and start_time fields adjusted to be 12:00:00 am. The original event will have its
    et and end_time fields adjusted be 11:59:59 pm. 
*/
void splitEvent(event_node *event, configuration_info *configInfo);

void setFonts(event_node *event, configuration_info *configInfo);

void setColors(event_node *event, configuration_info *configInfo);

   //modify the curEvent->st, curEvent->et, curEvent->start_time,
    //curEvent->end_time so they fall within the times displayed on the 
    //calendar.
    //NOTE: THE TIME STRING SHOULD STILL REFLECT ACTUAL START/STOP TIMES
void truncateTime(event_node *event, configuration_info *configInfo);


/*this will do "post processing" on all of the events that are in the week
  this includes:
  1. splitting events that span two days
  2. filling in the timeString field
  3. filling in the various fields in the options structure for each event. 
  4. truncating/deleting events that go beyond the limits of work_day
  5. determining the color an event should be colored. 
  6. Determining any other information needed to make the print out
*/
void postProcessEvents(event_node *firstEvent, configuration_info *configInfo);


#endif
