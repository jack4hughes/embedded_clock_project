#include "bitmap_displayer_mac.h"
#include "bitmap.h"

char map_bool_to_char(uint8_t bitmap_entry) {
  char character_to_return;
  switch (bitmap_entry) {
    case 0:
    character_to_return = BLANK_SQUARE_CHAR;
    break;
    
    case 1:
    character_to_return = FULL_SQUARE_CHAR;
    break;
  }
  return character_to_return;
}

int print_bitmap(uint8_t *bitmap_loc) {
  // Prints the current bitmap out to the screen.
  int i = 0;
  int col_number = 0;
  
  while (i < SCREEN_HEIGHT * SCREEN_WIDTH) {
    col_number = i % SCREEN_WIDTH;
    uint8_t *current_position = bitmap_loc + i;
    uint8_t current_character_bool = *current_position;
    char current_char = map_bool_to_char(current_character_bool);
    printf("%c", current_char);
    i++;
    if (col_number == SCREEN_WIDTH - 1) {  // End of row
        printf("\n");
    }; 
  }
  return 0;  // confirms that operation has been completed.
}

