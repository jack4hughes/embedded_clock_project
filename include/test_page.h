#ifndef TEST_PAGE_H
#define TEST_PAGE_H

//GLOBAL INPORTS:
#include <string.h>
#include <stdio.h>

//LOCAL IMPORTS:
#include "page.h"
#include "bitmap.h"
#include "time_getter_mac.h"

int test_timer_update(char *time_string);
//Updates the model of the clock every time a timer function is called (Just using a while loop to simulate this for now.)

int draw_test();
// Updates the bitmap with the current clock information. 

void test_input_update_function();
// Updates the clock based off inputs. Should do nothing atm.

ClockMode create_test_page();

#endif
