#include "bitmap_displayer_mac.h"
#include "bitmap.h"

int print_bitmap(int *bitmap_loc) {
  // Prints the current bitmap out to the screen.
    int i = 0;
    int col_number = 0;
    
    while (i < BITMAP_ROWS * BITMAP_COLS) {
        col_number = i % BITMAP_COLS;
        int current_character_bool = *(bitmap_loc + i);
        char current_char = map_bool_to_char(current_character_bool);
        printf("%c", current_char);
        i++;
        if (col_number == BITMAP_COLS - 1) {  // End of row
            printf("\n");
        }; 
    }
    return 0;  // Added return value
}

