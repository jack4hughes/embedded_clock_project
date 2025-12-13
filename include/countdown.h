#ifndef COUNTDOWN_H
#define COUNTDOWN_H

// Computer specific imports
#include <string.h>
#include <stdio.h>

// Local Defines. 
#include "time_getter_mac.h"
#include "page.h"
#include "bitmap.h"

int countdown_timer_update(char *time_string);

int draw_timer();

time_t get_countdown_end_time(time_t raw_time, time_t timer_length); 

int countdown_input_update(InputButtonTypes input);

char *get_countdown_string(time_t time_remaining, char *time_string_loc);

ClockMode create_countdown_page();

#endif


