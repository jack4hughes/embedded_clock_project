#include "time_getter_mac.h"
  
char * get_time_string(char *time_string_loc){
    // Get current time
  //
  // asdfasdfasdfasdf
    time_t raw_time;
    struct tm *time_info;
    
    time(&raw_time);
    time_info = localtime(&raw_time);
    
    // Format as "HH:MM" (24-hour format)
    strftime(time_string_loc, 6, "%H:%M", time_info);
    return time_string_loc;
};
