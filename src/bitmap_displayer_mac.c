#include "bitmap_displayer_mac.h"
#include "bitmap.h"

void clear_screen() {
  printf("\033[2J\033[H");
  fflush(stdout);
}


void cursor_home() {
  printf("\033[H");
  fflush(stdout);
} //Clears the terminal output (SLOW)


char *map_pixel_value_to_char(uint8_t character_entry) {
  if (character_entry == 0) {
    return BLOCK_EMPTY;
  }
  else if (character_entry < 64) {
    return BLOCK_LIGHT;
  }
  else if (character_entry < 128) {
    return BLOCK_MEDIUM;
  }

  else if (character_entry < 192) {
    return BLOCK_DARK; 
  }

  else if (character_entry == 255) {
    return BLOCK_FULL;
  }

  else {
    return BLOCK_EMPTY;
  }
}


int print_bitmap(uint8_t *bitmap_loc) {
  // Prints the current bitmap out to the screen.
  int i = 0;
  int col_number = 0;
  
  while (i < SCREEN_HEIGHT * SCREEN_WIDTH) {
  col_number = i % SCREEN_WIDTH;
    uint8_t *current_position = bitmap_loc + i;
    uint8_t current_pixel_value = *current_position;
    char * current_char = map_pixel_value_to_char(current_pixel_value);
    printf("%s", current_char);
    i++;
    if (col_number == SCREEN_WIDTH - 1) {  // End of row
        printf("\n");
    }; 
  }
  return 0;  // confirms that operation has been completed.
}

