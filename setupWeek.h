#ifndef CAL_SYSTEM_SETUP_WEEK_H
#define CAL_SYSTEM_SETUP_WEEK_H
#include "dataStructures.h"
//given relevant information will construct an icaltime_span that spans from
//00:00 on the first day to 23:59:59 on the second day. 
//preconditions: end day must be later than start day

//given configuration information this will create a week span that
//can be used to determine if an event occurs within a certain week
//NOTE: The create week span should only be used to determine
//if an even overlaps with days included in the work week.
struct icaltime_span createWeekSpan(configuration_info *configInfo);



work_week* createWorkWeek(configuration_info *configInfo);



#endif //!CAL_SYSTEM_SETUP_WEEK_H
