#include "test_page.h"

int test_timer_update(char *time_string){
  //this is a static page!
 return 0; 
}

int test_input_update(InputButtonTypes input) {
  // This module doesnt have interactions! 
  return 0;
}
//Updates the model of the clock every time a timer function is called (Just using a while loop to simulate this for now.)

int draw_test() {
  char test_overlay[SCREEN_HEIGHT][SCREEN_WIDTH] = {255};
  Bitmap test_overlay_bitmap = {
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    test_overlay
    };
  update_bitmap_with_string(&screen_bitmap, "0000", 0, 0);
};

// Updates the bitmap with the current clock information. 

int clock_input_update_function() {
  return 0;
};
// Updates the clock based off inputs. Should do nothing atm.

ClockMode create_test_page() {
  ClockMode test_page = {
    .timer_update_fn = test_timer_update,
    .input_update_fn = test_input_update,
    .draw_fn = draw_test,
    .init_fn = test_timer_update,
    .page_data = NULL,
  };
  return test_page; 
};

