#ifndef COUNTDOWN_H
#define COUNTDOWN_H

// Computer specific imports
#include <string.h>
#include <stdio.h>

// Local Defines. 
#include "time_getter_mac.h"
#include "page.h"
#include "bitmap.h"

// Define timer state enum,
typedef enum CountdownState {
  COUNTDOWN_INACTIVE,
  COUNTDOWN_ACTIVE,
  COUNTDOWN_PAUSED,
  COUNTDOWN_DONE,
} CountdownState;

/* User starts countdown:
   COUNTDOWN_INACTIVE -> COUNTDOWN_ACTIVE
   
   user pauses countdown:
   COUNTDOWN_ACTIVE -> COUNTDOWN_PAUSED

   user unpauses countdown:
   COUNTDOWN_PAUSED -> COUNTDOWN_ACTIVE 
   
   countdown finishes:
   COUNTDOWN_ACTIVE -> COUNTDOWN_DONE
   
   user resets countdown:
   COUNTDOWN_DONE -> COUNTDOWN INACTIVE.
   
   the user should only be able to change the
   countdown time if the countdown is in COUNTDOWN_INACTIVE state.*/

//define countdown edit enum.
typedef enum CountdownEditState {
  EDIT_HOURS,
  EDIT_MINS,
  EDIT_SECS,
  INACTIVE,
} CountdownEditState;

/* State machine logic:
EDIT_HOURS -> 
EDIT_MINS -> 
EDIT_SECS -> 
INACTIVE -> 
EDIT_HOURS

Can only go from INACTIVE to EDIT_HOURS if countdown
is in INACTIVE state. Once toggled to EDIT_INACTIVE
it will return to COUNTDOWN_PAUSED state.
*/

int countdown_timer_update(char *time_string);

int draw_timer();

time_t get_timer_end_time(time_t raw_time, time_t timer_length); 

int countdown_input_update(char input);

int clock_input_update_function();

char *get_countdown_string(time_t time_remaining, char *time_string_loc);

ClockMode create_timer_page();

#endif


