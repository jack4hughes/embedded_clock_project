/* this file holds the logic for the clock and the timer, as these can both be
 * implementd in a very similar way. The timer decrements the time, while the
 * clock increases it. The timer is also capped at 13 hours, while the clock
 * can display 24 hr time.
 */
#include <stdint.h>

typedef struct Time {
  uint8_t hours;
  uint8_t minut;
  uint32_t raw_time; //the number of seconds since midnight/# of secs remaining.
  uint32_t gmt_offset;
  uint8_t twelve_hr; //decides if the time should be 12 or 24 hour.
  uint8_t am_or_pm; //maybe this doesnt need to have state?
} Time;
/* This is our time struct, it holds the current time with some stateful properties.
 */

void init_time(
  *Time time_loc, 
  uint8_t hours, 
  uint8_t minutes, 
  uint8_t seconds
)
  /* This function intialises a time that has already been declared in memory.
   * It is generally used for setting the alarm and setting the current time on
   * boot.*/

void update_time(
    *Time current_time, 
    uint32 seconds_to_add
    );
// Updates the hour, minute and second values when the raw time gets updated.

void change_time_zone(*time current_time, uint8_t hrs_forward);
//changes the current time zone.

void increment_time(*Time current_time);
//increases raw time by 1.

void decrement_time(*Time time);
// decreases raw time by 1.
