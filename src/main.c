#include "bitmap.h"
#include "bitmap_displayer_mac.h"
#include "time_getter_mac.h"
#include "page.h"

int initialise_screen() {
  init_fonts(); //initialises the fonts in memory. 
  init_screen_bitmap(); //initialises the screen bitmap within memory.
  return 0;
}

int screen_update_loop() {
  char time_string[6];
  get_time_string(time_string);
  update_bitmap_with_string(&screen_bitmap, time_string, 0, 0);
  print_bitmap(screen_bitmap.bitmap_loc);
  return 0;
}


int main(void) {
  init_page_state_machine();
  Page *page = get_next_page();
  printf("page location: %x\n", page);
  /* initialise_screen();
  while(1) {
  //define numbers. (not needed here any more?)
    screen_update_loop();
    //Using scanf to halt for now.
     struct timespec ts, rem;
    ts.tv_sec= 0;
    ts.tv_nsec = 8333 * 1000;

    int nanosleep_complete = nanosleep(&ts, &rem); // Shohyld reprint 10 times pwr second.
    clear_screen();
  } */
}
