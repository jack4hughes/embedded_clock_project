#include <signal.h>
#include <stdlib.h>
#include <termios.h>
#include "bitmap.h"
#include "bitmap_displayer_mac.h"
#include "time_getter_mac.h"
#include "page.h"
#include "clock.h"

static struct termios standard_termios;
static int terminal_modified = 0
;
void cleanup_terminal() {
  printf("\033[?25h");  // Show cursor
  printf("\033[0m");    // Reset colors/formatting
  fflush(stdout);
}

void signal_handler(int signum) {
  cleanup_terminal();
  exit(signum);
}

int initialise_screen() {
  init_fonts(); //initialises the fonts in memory. 
  init_screen_bitmap(); //initialises the screen bitmap within memory.
  clear_screen();
  return 0;
}
int screen_update_loop(Page *current_page) {

  signal(SIGINT, signal_handler);
  
  // Also register cleanup for normal exit
  atexit(cleanup_terminal);

  char time_string[6];
  get_time_string(time_string);
  current_page->timer_update_fn(time_string);
  current_page->draw_fn();
  print_bitmap(screen_bitmap.bitmap_loc);
  return 0;
}

int main(void) {
  init_page_state_machine();
  Page clock_page = create_clock_page();
  printf("Clock Page Location: %x\n", &clock_page);
  add_page(&clock_page);
  Page *page = get_next_page();
  printf("page location: %x\n", page);
  initialise_screen();
  
  // Setting up the time for each loop.
  struct timespec ts, rem;
  ts.tv_sec = 0;
  ts.tv_nsec = 8333 + 1000000;

  while(1) {
  //define numbers. (not needed here any more?)
    // clear_screen();
    screen_update_loop(page);
    //Using scanf to halt for now.
    int nanosleep_complete = nanosleep(&ts, &rem); // Shohyld reprint 10 times pwr second.
    if (nanosleep_complete != 0) {
      nanosleep(&rem, &rem); // suspends the timer if thread is interrupted by signal.
    }
  }
}
