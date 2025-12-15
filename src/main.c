#include <signal.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "bitmap.h"

// Need to replace these for embedded! 
#include "bitmap_displayer_mac.h"
#include "time_getter_mac.h"
#include "page.h"
#include "clock.h"
#include "test_page.h"
#include "countdown.h"

#define MILLISECOND_MULTIPLIER 1000000

char time_string[9] = {0}; //defines the main time string.

int screen_update_loop(ClockMode *current_page) {
  get_time_string(time_string);
  int timer_update_status = current_page->timer_update_fn(time_string); //should return a 1 if error occurs.
  int draw_status = current_page->draw_fn(); //should return a 2 if error occurs.
  print_bitmap(screen_bitmap.bitmap_loc);
  print_buffer(); //this should be working!
  return 0;
}

int input_handler(char input, ClockMode **page) {
  //needs to be moved to bitmap_displayer_mac at some point!
  switch (input) {
    case ' ': {
      // need to move this function out to bitmap.c
      int clear_overlay[SCREEN_WIDTH][SCREEN_HEIGHT]  = {0}; //clears page buffer.
      Bitmap clear_overlay_bitmap = {
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        clear_overlay
      }; //from bitmap.h

      overlay_bitmaps(&screen_bitmap, clear_overlay_bitmap, 0, 0);
      *page = get_next_page(); //Changes page reference pointer in main logic flow.
      break;
      }
    case 'q':
      **page;
      exit(0);
      break;//quit
   
    case 'w':
      (*page)->input_update_fn(UP_BUTTON);
      write_input(UP_BUTTON);
      return 0;
    case 'a':
      (*page)->input_update_fn(EDIT_BUTTON);
      write_input(EDIT_BUTTON);
      return 0; //This will be our first button.

    case 's':
      (*page)->input_update_fn(DOWN_BUTTON);
      write_input(DOWN_BUTTON);
      return 0;

    case 'd':
      (*page)->input_update_fn(MODE_BUTTON);
      write_input(MODE_BUTTON);
      return 0;
       
    default:
      return 0;
    break;
  }
}


int main(void) {
  init_page_state_machine();

  ClockMode clock_page = create_clock_page();
  ClockMode test_page = create_test_page();
  ClockMode countdown_page = create_countdown_page();

  int add_clock_page = add_page(&clock_page);
  int add_test_page = add_page(&test_page);
  int add_countdown_page = add_page(&countdown_page);

  ClockMode *page = get_next_page();

  //set up IO
  init_term_io();
  hide_cursor(); 

  // Setting up the time for each loop.
  struct timespec ts, rem;
  ts.tv_sec = 0;
  ts.tv_nsec = 50 * MILLISECOND_MULTIPLIER; //60fps!
  
 while(1) {
    char input;
    int user_input_received = read(STDIN_FILENO, &input, 1);
  
    if (user_input_received == 1) {
      input_handler(input, &page);
    }
  
    // Always update screen, regardless of input
    screen_update_loop(page);
    
    // ADD THIS - actually sleep to control framerate
  }  
}
