#include "countdown.h"
#include "time.h"

/* THIS IS A COUNTDOWN!*/
static time_t timer_end_time;          //The end time for the timer.
static char remaining_time_string[16]; //Static buffer for time string.
static int timer_state;               //check if timer is active.

int countdown_timer_update(char *time_string) {
  /* Handles the timer logic asssociated with an update input. Shouldn't 
   * handle drawing directly, instead it should upodate the time remaining string.
   *
   * INPUTS: raw time, time remaining string position.*/
  switch(timer_state) {
    case COUNTDOWN_INACTIVE:
      return 0; //do nothing.

    case COUNTDOWN_ACTIVE:
      time_t raw_time = time(NULL);
      // Compare raw time to timer_end_time.
      // update time remaining.
      time_t time_remaining = timer_end_time - raw_time;
      
      //Change state if countdown is done.
      if (time_remaining <= 0) {
        timer_state = COUNTDOWN_DONE;
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

int countdown_input_update(char input) {
  switch(input) {
    case 0:
      return 0;
  }
  return 0;
}

int draw_timer() {
  update_bitmap_with_string(&screen_bitmap, remaining_time_string, 0, 0);
  return 0; //Need to check that update_bitmap_with_string doesnt return error codes.
}

time_t get_timer_end_time(time_t raw_time, time_t timer_length) {
  //need to implement this!
  time_t end_time = raw_time + timer_length;
  return end_time;
}

char *get_countdown_string(time_t time_remaining, char *time_string_loc){
    struct tm *time_info;
    time_info = localtime(&time_remaining);
    strftime(time_string_loc, 9, "%H:%M:%S", time_info); //This should give us the remaining time! 
    return 0;
};

int reset_timer(time_t raw_time) {
  //resets the timer.
}

int init_timer() {
  get_countdown_string(0, remaining_time_string);

  return 0;
}

ClockMode create_timer_page() {
  ClockMode timer_page = {
    .timer_update_fn = countdown_timer_update,
    .input_update_fn = countdown_input_update,
    .draw_fn = draw_timer,
    .init_fn = init_timer,
  };
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
