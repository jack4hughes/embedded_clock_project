#include "bitmap.h"
// #include "bitmaps.h"
#include "stdio.h"

//defining our externs in the C file.
Bitmap character_bitmaps[10];
Bitmap colon;
Bitmap blank;
uint8_t screen_bitmap_array[SCREEN_HEIGHT][SCREEN_WIDTH]; //This should be the only bitmap we store (i think.)
Bitmap screen_bitmap;

// Bitmap definitions (fonts basically)
const uint8_t BLANK_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH] = {
  {0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0}
};

const uint8_t ZERO_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH] = {
  {255, 255, 255, 255, 255},
  {255, 0, 0, 0, 255},
  {255, 0, 0, 0, 255},
  {255, 0, 0, 0, 255},
  {255, 255, 255, 255, 255}
};

const uint8_t ONE_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH] = {
  {0, 0, 255, 0, 0}, 
  {0, 0, 255, 0, 0},
  {0, 0, 255, 0, 0},
  {0, 0, 255, 0, 0},
  {0, 0, 255, 0, 0}
};

const uint8_t TWO_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH] = {
  {255, 255, 255, 255, 255}, 
  {0, 0, 0, 0, 255},
  {255, 255, 255, 255, 255},
  {255, 0, 0, 0, 0},
  {255, 255, 255, 255, 255}
};  

const uint8_t THREE_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH] = {
  {255, 255, 255, 255, 255}, 
  {0, 0, 0, 0, 255},
  {255, 255, 255, 255, 255},
  {0, 0, 0, 0, 255},
  {255, 255, 255, 255, 255}
};

const uint8_t FOUR_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH] = {
  {0, 255, 255, 255, 0}, 
  {255, 0, 0, 255, 0},
  {255, 255, 255, 255, 255},
  {0, 0, 0, 255, 0},
  {0, 0, 0, 255, 0}
};

const uint8_t FIVE_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH] = {
  {255, 255, 255, 255, 255}, 
  {255, 0, 0, 0, 0},
  {255, 255, 255, 255, 255},
  {0, 0, 0, 0, 255},
  {255, 255, 255, 255, 255}
};

const uint8_t SIX_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH] = {
  {255, 255, 255, 255, 255}, 
  {255, 0, 0, 0, 0},
  {255, 255, 255, 255, 255},
  {255, 0, 0, 0, 255},
  {255, 255, 255, 255, 255}
};

const uint8_t SEVEN_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH] = {
  {255, 255, 255, 255, 255}, 
  {0, 0, 0, 0, 255},
  {0, 0, 0, 255, 0},
  {0, 0, 0, 255, 0},
  {0, 0, 255, 0, 0}
};

//uint8_t: create fonts from here on down.
const uint8_t EIGHT_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH] = {
  {255, 255, 255, 255, 255}, 
  {255, 0, 0, 0, 255},
  {255, 255, 255, 255, 255},
  {255, 0, 0, 0, 255},
  {255, 255, 255, 255, 255}
};


const uint8_t NINE_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH] = {
  
  {255, 255, 255, 255, 255}, 
  {255, 0, 0, 0, 255},
  {255, 255, 255, 255, 255},
  {0, 0, 0, 0, 255},
  {0, 0, 0, 0, 255}
};


const uint8_t COLON_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH] =  {
  {0, 0, 0, 0, 0}, 
  {0, 0, 255, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 255, 0, 0},
  {0, 0, 0, 0, 0}
};



Bitmap create_bitmap(
  uint8_t width, 
  uint8_t height, 
  const uint8_t *bitmap_loc) {
  Bitmap character;
  // sets the character information.  
  character.width = width;
  character.height = height;
  character.bitmap_loc = bitmap_loc;
  
  return character;
}

uint8_t get_character_bool_from_position(
  Bitmap character, 
  uint8_t row, 
  uint8_t col) {
  
  const uint8_t offset = col + character.width * row;
  const uint8_t *bitmap_pos = character.bitmap_loc + offset;
  int bitmap_bool = *bitmap_pos;
  return bitmap_bool;
  
}

Bitmap get_character_bitmap(char character) {
  // Mapping 1 
  switch(character) {
    case '0':
      return character_bitmaps[0] ;
      break;
    case '1':
      return character_bitmaps[1] ;
      break;
    case '2':
      return character_bitmaps[2];
      break;
    case '3':
      return character_bitmaps[3];
      break;
    case '4':
      return character_bitmaps[4];
      break;
    case '5':
      return character_bitmaps[5];
      break;
    case '6':
      return character_bitmaps[6];
      break;
    case '7':
      return character_bitmaps[7];
      break;
    case '8':
      return character_bitmaps[8];
      break;
    case '9':
      return character_bitmaps[9];
      break;
    case ':':
      return colon;
      break;
    default:
      return colon;
      break;
  };
}

void overlay_bitmaps(
    Bitmap *underlay,
    Bitmap overlay,
    uint8_t start_col, 
    uint8_t start_row) 
    {
    uint8_t pos_within_overlay = 0;
    uint16_t pos_within_underlay = start_row * SCREEN_WIDTH + start_col;
    
    while (pos_within_overlay < overlay.height * overlay.width) {
        // Copy the data BEFORE incrementing positions
        uint8_t *underlay_pos_pointer = underlay->bitmap_loc + pos_within_underlay;
        const uint8_t *overlay_pos_pointer = overlay.bitmap_loc + pos_within_overlay;
        
        if (pos_within_underlay < SCREEN_HEIGHT * SCREEN_WIDTH) { // guard against improper assignment
            *underlay_pos_pointer = *overlay_pos_pointer;
        }
        // Now increment positions
        pos_within_overlay++;
        pos_within_underlay++;
        
        // Moving down a line if the overlay has reached the end of its row
        if (pos_within_overlay % overlay.width == 0) {
            pos_within_underlay += (SCREEN_WIDTH - overlay.width);
        }
    }
}


uint8_t check_string_length(char *str_ptr) {
  uint8_t string_length = 0;
  char current_char = *str_ptr;
  while (current_char != '\0') {
    string_length++;
    str_ptr++;
    current_char = *str_ptr;
  }
  return string_length;  // This was missing!
}

void update_bitmap_with_string(
  Bitmap *bitmap, 
  char *str_ptr, 
  uint8_t start_row, 
  uint8_t start_col) {
  //only works with fixed size characters for now!
  unsigned int string_length = check_string_length(str_ptr);
  char current_char = *str_ptr;
  
  if (string_length * 5 <  SCREEN_WIDTH) {
    while (current_char != '\0') {  //Automatic halting at end of string.
      Bitmap character_bitmap = get_character_bitmap(current_char);
      overlay_bitmaps(bitmap, character_bitmap, start_col, start_row);
      start_col += character_bitmap.width + 1; // Adds a one pixel space between each letter.
      str_ptr++;
      current_char = *str_ptr;
    }
  }
}

void init_fonts() {
    //defining character_bitmaps/
    character_bitmaps[0] = create_bitmap(5, 5, (const uint8_t*)ZERO_5X5);
    character_bitmaps[1] = create_bitmap(5, 5, (const uint8_t*)ONE_5X5);
    character_bitmaps[2] = create_bitmap(5, 5, (const uint8_t*)TWO_5X5);
    character_bitmaps[3] = create_bitmap(5, 5, (const uint8_t*)THREE_5X5);
    character_bitmaps[4] = create_bitmap(5, 5, (const uint8_t*)FOUR_5X5);
    character_bitmaps[5] = create_bitmap(5, 5, (const uint8_t*)FIVE_5X5);
    character_bitmaps[6] = create_bitmap(5, 5, (const uint8_t*)SIX_5X5);
    character_bitmaps[7] = create_bitmap(5, 5, (const uint8_t*)SEVEN_5X5);
    character_bitmaps[8] = create_bitmap(5, 5, (const uint8_t*)EIGHT_5X5);
    character_bitmaps[9] = create_bitmap(5, 5, (const uint8_t*)NINE_5X5);
    
    //defining non-number characters(this will eventually contain whole
    //alphabet!)
    colon = create_bitmap(5, 5, (const uint8_t*)COLON_5X5);
    blank = create_bitmap(5, 5, (const uint8_t*)BLANK_5X5);
};

void reset_screen_bitmap() {
  //set every element in screen to 0.
  uint8_t i = 0;
  uint8_t j = 0;

  while (i < SCREEN_HEIGHT) {
    while (j < SCREEN_WIDTH) {
      uint8_t *screen_pixel_pointer = screen_bitmap.bitmap_loc + SCREEN_WIDTH * i + j;
      *screen_pixel_pointer = 0; 
      j++;
    }
  i++;
  }
}

void init_screen_bitmap() {
  screen_bitmap = create_bitmap(SCREEN_HEIGHT, SCREEN_WIDTH, (const uint8_t*)screen_bitmap_array);
  reset_screen_bitmap();
}
