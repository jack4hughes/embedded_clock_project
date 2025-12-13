#ifndef PAGE_H
#define PAGE_H

#include "stdint.h"
#include "stdio.h"

#define MAX_NUMBER_OF_PAGES 16
typedef enum ClockModeInput {
  SWITCH_STATE,      // Switches state.
  BUTTON,            // Standard button.
  EDIT,              // Edit button.
} ClockModeInput;

typedef struct ClockMode {
  int (*timer_update_fn)(char *time_string); // Time string created by OS, so we need to pass this as a function. 
  int (*input_update_fn)(char input);
  int (*draw_fn)(); //Doesnt need bitmap location as this is a signleton.
  int (*init_fn)();
  void* page_data;
} ClockMode;

typedef struct ClockModeStateMachine {
  ClockMode *pages[MAX_NUMBER_OF_PAGES]; //Three pages for now, Clock, Alarm and Timer.
  uint8_t active_index;
  uint8_t number_of_pages; // The last populated index. Different from MAX_NUMBER_OF_PAGES which is the highest assignable index.
  ClockMode *active_page;
} ClockModeStateMachine;


//Enums: This is where all the enums for page edit functions are stored.
//
//
typedef enum EditTimeState {\
  EDIT_HOURS,
  EDIT_MINS,
  EDIT_SECS,
  EDIT_INACTIVE
} EditTimeState;

typedef enum InputButtonStates {
  MODE_BUTTON,
  EDIT_BUTTONM,
  SNOOZE_BUTTON,
  UP_BUTTON,
  DOWN_BUTTON,
} InputButtonStates;

//Functions:
int init_page_state_machine();
// initialised page_state_machine

ClockMode *get_next_page();
//returns a pointer to the next valid page.

int add_page(ClockMode *page_loc);
//Allows a new page to be added to the ClockModeStateMachine, and returns the index.

#endif

