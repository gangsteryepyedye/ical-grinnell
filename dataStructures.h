/** @file
   @brief  Data structures used for the iCal project

   @details Each work_week contains an array of seven work_days. Each work_day is 
   a linked list of event_nodes. And each event_node contains the all the information needed
   to properly display the event on a printed work week calendar.

   @remark 
   Not all of the data structures defined here are actually used in meaningful way. They
   are provided simply as place holders for future enhancements. 
*/
#ifndef CAL_SYSTEM_DATA_STRUCTURES_H
#define CAL_SYSTEM_DATA_STRUCTURES_H

#include <stdbool.h>
#include "calEnum.h"


//this will not be used during the initial prototyping stage
//the front end does not have to worry about this part

/** @brief
    The filter options struct contains two arrays of strings, describing types of events 
    to omit.
*/
typedef struct _filter_options{
  char ** categoriesToOmit; /**< Categories of events that should be ommited, ie appointment*/
  char ** clasificationsToOmit; /**< Events of these classes are ommited. */

} filter_options;


/** brief
    The @c node_options struct contains information about how an event should be displayed
*/
typedef struct _node_options{
  enum color box_color, text_color;
  enum font time_font, summary_font, location_font;
  //more to be added later. 
} node_options;


//event_node is the data structure for storing all information about a particular event

/** @brief
    The @c event_node structure stores all information used determine what infromation about
    the event is displayed, and how that information is displayed
    
    @details
    
*/
typedef struct _event_node{
  //any event we display must have an identifiable beginning and end
  time_t  start_time; /**< the start time of the event */
  time_t end_time; /**< the end time of the event */
  struct tm *st; /**< the start time of the event */
  struct tm *et; /**< the end time of the event */
  //strings storing the summary and location fields for this event
  //note: summary is likely what would be called "name" in normal circumstances

  char *summary; /**< Summary of the event. Likely a name, ie CSC-161*/
  char *location; /**< The location where the event takes place, ie "SCI 3819"*/
  char*timeString; /**< A string of the start and end time of the event. Ie 8:00-9:00 */

  //the options that describe how this node should be displayed
  //note these are not used currently, but functions should be written so that 
  //the options can be easily taken into account. 
  node_options *options; /**< Options describing how this specific event should be displayed*/

  //a pointer to the next event. The next event MUST start after this event starts.
  struct _event_node *next_event; /**< Another event_node */

} event_node;

/** @brief
    The @c work_day structure contains only the pointer to the first @c event_node
*/
typedef struct _work_day{
  event_node *first_event;
} work_day;

/** @brief
    The @c work_week struct contains both each @c work_day, and information about the work week.
*/
    
typedef struct _work_week{
  //an array of 7 work_days, we know that there will be at most 7 days in a work week.
  work_day *day[7]; /**< The array of seven work_days */
  //number of days is simply how many days are in a work week.
  //firstDay is [0,6] with sunday = 0;
  int firstDay; /**< The first day of the work_week, a number 0-6 with 0 = Sunday */
  int lastDay; /**< The last day of the work_week, a number 0-6 with 0 = Sunday */
  int startOfDayHour; /**< The hour at which a work day begins, an integer 0-23 */
  int  startOfDayMinute; /**< The minute at which the work day begins, an integer 0-59 */
  int endOfDayHour; /**< The hour at which a work day ends, an integer 0-23 */
  int  endOfDayMinute; /**< The minute at which the work day ends, an integer 0-59 */  
}work_week;


/** @brief
    The @c ruleNode structure contains information that defines a rule

    @details Rule are evaluated as follows. For a specific event, if the rule antecedent field have
    the value of antecedentValue then that event has the rule consequent field set to be consequentValue
*/
typedef struct _ruleNode{
  enum ruleAntecedentField raf;
  enum ruleConsequentField rcf;
  char *antecedentValue;
  char * consequentValue;
  struct _ruleNode *nextRule;
} ruleNode;

typedef struct _configurationInfo{
  int startOfDayHour, startOfDayMinute, endOfDayHour, endOfDayMinute;
  enum color defaultFontColor, defaultBoxColor;
  enum font timeFont, summaryFont, locationFont;
  enum day_of_week firstDayOfWeek, lastDayOfWeek;
  ruleNode *rules;
  
  bool twentyFourHourTime;
  int startMonth, startMDay, startYear, endMonth, endMDay, endYear;
  char *nameOfOutputFile;
} configuration_info;
#endif /* !CAL_SYSTEM_DATA_STRUCTURES_H */
