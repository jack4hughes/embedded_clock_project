#include "countdown.h"
/* THIS IS A COUNTDOWN!*/

// Define timer states,
typedef enum CountdownState {
  COUNTDOWN_INACTIVE,          //Can go to COUNTDOWN_ACTIVE & COUNTDOWN_EDIT
  COUNTDOWN_ACTIVE,            //Can go to COUNTDOWN_PAUSED & COUNTDOWN_DONE
  COUNTDOWN_PAUSED,            //Can go to COUNTDOWN_INACTIVE & COUNTDOWN_ACTIVE
  COUNTDOWN_EDIT,              //Can go to COUNTDOWN_INACTIVE
  COUNTDOWN_DONE,              //Can go to COUNTDOWN_INACTIVE
} CountdownState;


// Static variables.
static time_t countdown_end_time = 0;
static time_t countdown_time = 0;
static char remaining_time_string[16];
static CountdownState countdown_state = COUNTDOWN_INACTIVE;
static EditTimeState countdown_edit_state = EDIT_INACTIVE;
static int timer_length;

//initialising enums.
int countdown_timer_update(char *time_string) {
  /* Handles the timer logic asssociated with an update input. Shouldn't 
   * handle drawing directly, instead it should upodate the time remaining string.
   *
   * INPUTS: raw time, time remaining string position.*/
  time_t time_remaining = 0;

  switch(countdown_state) {
    case COUNTDOWN_INACTIVE: {
      //do nothing.
      break;
    }

    case COUNTDOWN_ACTIVE: {
      time_t raw_time = time(NULL);
      // Compare raw time to countdown_end_time.
      // update time remaining.
      time_t time_remaining = countdown_end_time - raw_time;
           //Change state if countdown is done.
      if (time_remaining <= 0) {
        countdown_state = COUNTDOWN_DONE;
        time_remaining = 0;
      }
      return 0;
      break;
    }

    case COUNTDOWN_PAUSED: {
      // Do nothing.
      // This is the same as COUNTDOWN_INACTIVE but its a different state so 
      // modelled differently in case anything is changed in the future.
      return 0;
      break;
    }

    case COUNTDOWN_EDIT: {
      //Again, does nothing.
      return 0;
      break;
    }

    case COUNTDOWN_DONE: {
      // wait for user input cancelling timer.
      // Display 00:00.
      // Make a noise.
      return 0;
      break;
    }
    default:
      //this should never happen. The state machine has entered an invalid state.
      return 1;
      break;
  }
  get_countdown_string(countdown_time, remaining_time_string);
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

int remove_time_from_countdown(void) {
  int countdown_time_buffer = countdown_time;
  switch(countdown_edit_state) {
    case EDIT_INACTIVE:
      return 1; //shouldnt be reached!
    case EDIT_HOURS:
      countdown_time_buffer -= 3600;
    case EDIT_MINS:
      countdown_time_buffer -= 60;
    case EDIT_SECS:
      countdown_time_buffer -= 1;
  }
  
  //make sure that negative times cant be reached.
  if (countdown_time_buffer >= 0) {
    countdown_time = countdown_time_buffer;
  }
  else {
    countdown_time = 0;
  }
  return countdown_time;
}

CountdownState countdown_edit_button_state_change(CountdownState current_state) {
  //This function handles changes in the countdown state because of user inputs.
  switch (current_state) {
    case COUNTDOWN_INACTIVE:
      countdown_edit_state = EDIT_HOURS;
      return COUNTDOWN_EDIT;
    
    case COUNTDOWN_PAUSED:
      return 0; 

    case COUNTDOWN_EDIT:    
      if (countdown_edit_state == EDIT_SECS) {
        return COUNTDOWN_INACTIVE;
      }
      else {
        return COUNTDOWN_EDIT;
      }
    case COUNTDOWN_DONE:
      countdown_edit_state = EDIT_HOURS;
      return COUNTDOWN_EDIT; //Not entirely sure if this is a valid path.
    default:
      return COUNTDOWN_INACTIVE;
  }
}

int countdown_input_update(InputButtonTypes input) {
  switch(input) {
    case MODE_BUTTON:
      //should be handled above this module! Keeping explicit for now.
      return 1;

    case EDIT_BUTTON: {
      countdown_state = countdown_edit_button_state_change(countdown_state);
    }
    case SNOOZE_BUTTON: {
      //
      if (countdown_state == COUNTDOWN_ACTIVE) {
        countdown_state = COUNTDOWN_PAUSED;
      }
      if (countdown_state == COUNTDOWN_PAUSED) {
        countdown_state = COUNTDOWN_ACTIVE;
      }
      return 0;
    }

    case UP_BUTTON: {
      if (countdown_state == COUNTDOWN_EDIT) {
        add_time_to_countdown();
      }
      return 0;
    }

    case DOWN_BUTTON: {
      if (countdown_state == COUNTDOWN_EDIT) {
        remove_time_from_countdown(); 
      }
      return 0;

    default:
      //called whenever this function encounters an unhandled path.
      return 1;
    }
  }
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

char *get_countdown_string(time_t time_remaining, char *time_string_loc) {
    int hours = time_remaining / 3600;
    int minutes = (time_remaining % 3600) / 60;
    int seconds = time_remaining % 60;
    
    snprintf(time_string_loc, 9, "%02d:%02d:%02d\n", hours, minutes, seconds);
    return time_string_loc; 
}


int reset_countdown(time_t raw_time) {
  //resets the coujntdown.
  /*Needs a static variable with the countdown time duration to work.
   */
}

int init_countdown() {
  countdown_time = 15 * 60;
  get_countdown_string(countdown_time, remaining_time_string);
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
