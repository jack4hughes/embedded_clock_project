#include "bitmap.h"
#include "bitmap_displayer_mac.h"
#include "time_getter_mac.h"

int main(void) {
    //define numbers. (not needed here any more?)
    init_fonts(); //initialises the fonts in memory. 
    init_screen_bitmap(); //initialises the screen bitmap within memory.
    
    char time_string[6];
    get_time_string(time_string);
    update_bitmap_with_string(&screen_bitmap, time_string, 0, 0);
    print_bitmap(screen_bitmap.bitmap_loc);
    return 0;  // Added return value
}
