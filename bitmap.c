#include "bitmap.h"
// #include "bitmaps.h"
#include "stdio.h"

const int BLANK[5][5] = {
  {0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0}
};

const int ZERO_5X5[5][5] = {
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 1, 1, 1, 1}
};

const int ONE_5X5[5][5] = {
  {0, 0, 1, 0, 0}, 
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0}
};

const int TWO_5X5[5][5] = {
  {1, 1, 1, 1, 1}, 
  {0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0},
  {1, 1, 1, 1, 1}
};

const int THREE_5X5[5][5] = {
  {1, 1, 1, 1, 1}, 
  {0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1},
  {0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1}
};

const int FOUR_5X5[5][5] = {
  {0, 1, 1, 1, 0}, 
  {1, 0, 0, 1, 0},
  {1, 1, 1, 1, 1},
  {0, 0, 0, 1, 0},
  {0, 0, 0, 1, 0}
};

const int FIVE_5X5[5][5] = {
  {1, 1, 1, 1, 1}, 
  {1, 0, 0, 0, 0},
  {1, 1, 1, 1, 1},
  {0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1}
};

const int SIX_5X5[5][5] = {
  {1, 1, 1, 1, 1}, 
  {1, 0, 0, 0, 0},
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 1},
  {1, 1, 1, 1, 1}
};

const int SEVEN_5X5[5][5] = {
  {1, 1, 1, 1, 1}, 
  {0, 0, 0, 0, 1},
  {0, 0, 0, 1, 0},
  {0, 0, 0, 1, 0},
  {0, 0, 1, 0, 0}
};

//TODO: create fonts from here on down.
const int EIGHT_5X5[5][5] = {
  {1, 1, 1, 1, 1}, 
  {1, 0, 0, 0, 1},
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 1},
  {1, 1, 1, 1, 1}
};

const int NINE_5X5[5][5] = {
  {1, 1, 1, 1, 1}, 
  {1, 0, 0, 0, 1},
  {1, 1, 1, 1, 1},
  {0, 0, 0, 0, 1},
  {0, 0, 0, 0, 1}
};

const int COLON_5X5[5][5] =  {
  {0, 0, 0, 0, 0}, 
  {0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0}
};

Character create_character(
  //creates a character from information.
  int number, 
  int width, 
  int height, 
  const int *bitmap_loc) {
  
  Character character;
  character.char_representation = number;
  character.width = width;
  character.height = height;
  character.bitmap_loc = bitmap_loc;

  return character;
}

int map_bool_to_char(int bitmap_entry) {
  /* maps the boolean values in our bitmap to characters for printing to the
   * terminal. Makes debugging easier.
   *
   * for example if 0 is mapped to '.' any zero in the bitmap will lead to a .
   * being printied on the screen. You can chance the characters or strings (if
   * you want colour in the .h file.*/
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

int get_character_bool_from_position(
  Character character, 
  int row, 
  int col) {
  
  const int offset = col + character.width * row;
  const int *bitmap_pos = character.bitmap_loc + offset;
  int bitmap_bool = *bitmap_pos;
  return bitmap_bool;
  
}
\
Character char_to_character_converter(char character) {
  const Character zero = create_character(0, 5, 5, (const int*)ZERO_5X5);
  const Character one = create_character(1, 5, 5, (const int*)ONE_5X5);
  const Character two = create_character(1, 5, 5, (const int*)TWO_5X5);
  const Character three = create_character(1, 5, 5, (const int*)THREE_5X5);
  const Character four = create_character(1, 5, 5, (const int*)FOUR_5X5);
  const Character five = create_character(1, 5, 5, (const int*)FIVE_5X5);
  const Character six = create_character(1, 5, 5, (const int*)SIX_5X5);
  const Character seven = create_character(1, 5, 5, (const int*)SEVEN_5X5);
  const Character eight = create_character(1, 5, 5, (const int*)EIGHT_5X5);
  const Character nine = create_character(1, 5, 5, (const int*)NINE_5X5);
  const Character colon = create_character(1, 5, 5, (const int*)COLON_5X5);
  // Mapping 1 
  switch(character) {
    case '0':
      return zero;
      break;
    case '1':
      return one;
      break;
    case '2':
      return two;
      break;
    case '3':
      return three;
      break;
    case '4':
      return four;
      break;
    case '5':
      return five;
      break;
    case '6':
      return six;
      break;
    case '7':
      return seven;
      break;
    case '8':
      return eight;
      break;
    case '9':
      return nine;
      break;
    case ':':
      return colon;
      break;
    default:
      return colon;
      break;
  };
}
void add_character_to_bitmap(
    int *bitmap,
    Character character, 
    int start_col, 
    int start_row) {
    int pos_within_character = 0;
    int pos_within_bitmap = start_row * BITMAP_COLS + start_col;
    
    while (pos_within_character < character.height * character.width) {
        // Copy the data BEFORE incrementing positions
        int *bitmap_pos_pointer = bitmap + pos_within_bitmap;
        const int *character_pos_pointer = character.bitmap_loc + pos_within_character;
        
        if (pos_within_bitmap < BITMAP_ROWS * BITMAP_COLS) { //guard against improper assignment.
          *bitmap_pos_pointer = *character_pos_pointer;
         }
        // Now increment positions
        pos_within_character++;
        pos_within_bitmap++;
        
        // Moving down a line if the character has reached the end of its row
        if (pos_within_character % character.width == 0) {
            pos_within_bitmap += (BITMAP_COLS - character.width);
        }
    }
}

int check_string_length(char *str_ptr) {
  int string_length = 0;
  char current_char = *str_ptr;
  while (current_char != '\0') {
    string_length++;
    str_ptr++;
    current_char = *str_ptr;
  }
  return string_length;  // This was missing!
}

void update_bitmap_with_string(int *bitmap, char *str_ptr) {
  //only works with fixed size characters for now!
  int string_length = check_string_length(str_ptr);
  int current_char = *str_ptr;
  int start_col = 0;
  int start_row = 0;
  if (string_length * 5 <  BITMAP_COLS) {
    while (current_char != '\0') {
      Character character_bitmap = char_to_character_converter(current_char);
      add_character_to_bitmap(bitmap, character_bitmap, start_col, start_row);
      start_col += character_bitmap.width + 1;
      str_ptr++;
      current_char = *str_ptr;
    }
  }
};
