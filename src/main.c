#include <signal.h>
#include <stdlib.h>
#include <termios.h>
#include "bitmap.h"

// Need to replace these for embedded! 
#include "bitmap_displayer_mac.h"
#include "time_getter_mac.h"
#include "page.h"
#include "clock.h"

int screen_update_loop(Page *current_page) {

  initialise_screen(); 

  char time_string[6] = {0};
  get_time_string(time_string);
  current_page->timer_update_fn(time_string);
  current_page->draw_fn();
  print_bitmap(screen_bitmap.bitmap_loc);
  return 0;
}

int main(void) {
  init_page_state_machine();
  Page clock_page = create_clock_page();
  add_page(&clock_page);
  Page *page = get_next_page();
  initialise_screen();
  
  // Setting up the time for each loop.
  struct timespec ts, rem;
  ts.tv_sec = 0;
  ts.tv_nsec = 4000 + 1000000;
  
  int stop = 1; // used for testing purposes.
  while(stop) {
  //define numbers. (not needed here any more?)
    // clear_screen();
    screen_update_loop(page);
    //Using scanf to halt for now.
    int nanosleep_complete = nanosleep(&ts, &rem); // should redraw     if (nanosleep_complete != 0) {
      nanosleep(&rem, &rem); // suspends the timer if thread is interrupted by signal.
    }
  }
}
