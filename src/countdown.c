#include "countdown.h"
#include "time.h"

/* THIS IS A COUNTDOWN!*/

// Define timer states,
typedef enum CountdownState {
  COUNTDOWN_INACTIVE,
  COUNTDOWN_ACTIVE,
  COUNTDOWN_PAUSED,
  COUNTDOWN_DONE,
} CountdownState;

typedef enum CountdownEditState {
  EDIT_HOURS,
  EDIT_MINS,
  EDIT_SECS,
  EDIT_INACTIVE,
} CountdownEditState;

// Static variables.
static time_t countdown_end_time = 0;
static time_t countdown_time = 0;
static char remaining_time_string[16];
static CountdownState countdown_state = COUNTDOWN_INACTIVE;
static CountdownEditState countdown_edit_state = EDIT_INACTIVE;
static int timer_length;

//initialising enums.

int countdown_timer_update(char *time_string) {
  /* Handles the timer logic asssociated with an update input. Shouldn't 
   * handle drawing directly, instead it should upodate the time remaining string.
   *
   * INPUTS: raw time, time remaining string position.*/
  switch(countdown_state) {
    case COUNTDOWN_INACTIVE:
      return 0; //do nothing.

    case COUNTDOWN_ACTIVE:
      time_t raw_time = time(NULL);
      // Compare raw time to countdown_end_time.
      // update time remaining.
      time_t time_remaining = countdown_end_time - raw_time;
      
      //Change state if countdown is done.
      if (time_remaining <= 0) {
        countdown_state = COUNTDOWN_DONE;
        time_remaining = 0;
        get_countdown_string(time_remaining, time_string);
      }

      return 0;


    case COUNTDOWN_PAUSED:
      // Do nothing.
      return 0;

    case COUNTDOWN_DONE:
      // wait for user input cancelling timer.
      // Display 00:00.
      // Make a noise.
      return 0;
  }
  return 0; 
}

int add_time_to_countdown(void) {
  //increments one unit by 1. Unit decided by case.
  /* Increments countdown_time static variable and returns error value if called incorrectly.
   */
  switch(countdown_edit_state) {
    case EDIT_INACTIVE: 
      return 1;                //should never be called in this state. Returns error value.
    case EDIT_HOURS:
      countdown_time += 3600;
      return 0;
    case EDIT_MINS:
      countdown_time += 60;
      return 0;
    case EDIT_SECS:
      countdown_time += 1;
      return 0;
  }
}
int countdown_input_update(char input) {
  switch(input) {
    case 0:
      return 0;
  }
  return 0;
}

int draw_countdown() {
  update_bitmap_with_string(&screen_bitmap, remaining_time_string, 0, 0);
  return 0; //Need to check that update_bitmap_with_string doesnt return error codes.
}

time_t get_countdown_end_time(time_t raw_time, time_t countdown_length) {
  //need to implement this!
  time_t end_time = raw_time + countdown_length;
  return end_time;
}

char *get_countdown_string(time_t time_remaining, char *time_string_loc){
    struct tm *time_info;
    time_info = localtime(&time_remaining);
    strftime(time_string_loc, 9, "%H:%M:%S", time_info); //This should give us the remaining time! 
    return 0;
};

int reset_countdown(time_t raw_time) {
  //resets the coujntdown.
  /*Needs a static variable with the countdown time duration to work.
   */
}

int init_countdown() {
  countdown_end_time = 0;
  get_countdown_string(countdown_end_time, remaining_time_string);
  countdown_state = COUNTDOWN_INACTIVE;
  countdown_edit_state = EDIT_INACTIVE;

  return 0;
}

ClockMode create_countdown_page() {
  ClockMode countdown_page = {
    .timer_update_fn = countdown_timer_update,
    .input_update_fn = countdown_input_update,
    .draw_fn = draw_countdown,
    .init_fn = init_countdown,
  };
  return countdown_page;
}

/* CLOCK UPDATE PROFILE:
 * clock update called externally.
 * timer update called. -> returns a number that controls redraw.
 * bitmap updater called depending on timer update output.
*/ 

/* ADJUSTMENT LOGIC: 
 *  edit button pressed: handled externally.
 *  three edit options: Cancel timer (sets to inactive), reset timer (sets to previous timer start.)
 * */
