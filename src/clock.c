#include "clock.h"

static char *time_string_loc;

void clock_timer_update(char *time_string) {
  time_string_loc = time_string;
}

void draw_clock() {
  update_bitmap_with_string(&screen_bitmap, time_string_loc, 0, 0);
}

void adjust_clock(int input) {
  return; //do nothing for now.
}

void init_clock(int input) {
  return;
}

Page create_clock_page() {
  Page clock_page = {
    .timer_update_fn = clock_timer_update,
    .input_update_fn = adjust_clock,
    .draw_fn = draw_clock,
    .init_fn = init_clock,
    .page_data = NULL,
  };

  return clock_page;
}
