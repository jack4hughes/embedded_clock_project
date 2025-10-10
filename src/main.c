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

#define MILLISECOND_MULTIPLIER 1000000

char time_string[9] = {0}; //defines the main time string.

int screen_update_loop(Page *current_page) {
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
  add_page(&clock_page);
  Page *page = get_next_page();
  printf("new page created at %p", page);
  
  //set up IO
  init_term_io();
  
  // Setting up the time for each loop.
  struct timespec ts, rem;
  ts.tv_sec = 0;
  ts.tv_nsec = 17 * MILLISECOND_MULTIPLIER; //60fps!
  char *scan_start[128]; // scanf biffer incase people press buttons before enter.
  scanf("", &scan_start);
  //enter loop.
  while(1) {
    char input;
    screen_update_loop(page);
    int user_input_received = read(STDIN_FILENO, &input, 1);
    if (user_input_received == 1) {
      //process that input
      if (input == ' ') {
        page = get_next_page();
        screen_update_loop(page);
      }
      else {
        printf("recieved input: \'%c\'");
      }

      //display screen!
    }
    else if (user_input_received == 0) {
      screen_update_loop(page);
    }
   }
}
