#ifndef PAGE_H
#define PAGE_H
#include "stdint.h"
#include "stdio.h"

#define MAX_NUMBER_OF_PAGES 16

typedef struct Page {
  void (*timer_update_fn)(char *time_string); // Time string created by OS, so we need to pass this as a function. 
  void (*input_update_fn)(char input);
  void (*draw_fn)(); //Doesnt need bitmap location as this is a signleton.
  void (*init_fn)();
  void* page_data;
} Page;

typedef struct PageStateMachine {
  Page *pages[MAX_NUMBER_OF_PAGES]; //Three pages for now, Clock, Alarm and Timer.
  uint8_t active_index;
  uint8_t number_of_pages; // The last populated index. Different from MAX_NUMBER_OF_PAGES which is the highest assignable index.
  Page *active_page;
} PageStateMachine;

int init_page_state_machine();
// initialised page_state_machine

Page *get_next_page();
//returns a pointer to the next valid page.

int add_page(Page *page_loc);
//Allows a new page to be added to the PageStateMachine, and returns the index.
#endif

