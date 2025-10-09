#ifndef CLOCK_PAGE_H
#define CLOCK_PAGE_H

//GLOBAL INPORTS:
#include <string.h>
#include <stdio.h>

//LOCAL IMPORTS:
#include "page.h"
#include "bitmap.h"
#include "time_getter_mac.h"

void clock_timer_update(char *time_string);
//Updates the model of the clock every time a timer function is called (Just using a while loop to simulate this for now.)

void draw_clock();
// Updates the bitmap with the current clock information. 

void clock_input_update_function();
// Updates the clock based off inputs. Should do nothing atm.

Page create_clock_page();

#endif
