#include "clock.h"

static char *time_string_loc;

int clock_timer_update(char *time_string) {
  time_string_loc = time_string; //do we need this?
}

int draw_clock() {
  update_bitmap_with_string(&screen_bitmap, time_string_loc, 0, 0);
}

int adjust_clock(InputButtonTypes input) {
  return 0; //do nothing for now.
}

int init_clock() {
  return 0;
}

ClockMode create_clock_page() {
  ClockMode clock_page = {
    .timer_update_fn = clock_timer_update,
    .input_update_fn = adjust_clock,
    .draw_fn = draw_clock,
    .init_fn = init_clock,
    .page_data = NULL,
  };

  return clock_page;
}
