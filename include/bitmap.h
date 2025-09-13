/* This is the main module that deals with initialising and updating the
 * bitmap. The bitmap is assumed to have constant size.*/

#ifndef DISPLAY
#define DISPLAY

// Defining the size of our screen bitmap.
#define BITMAP_ROWS 5
#define BITMAP_COLS 30

//defining how our print statement should look.
#define FULL_SQUARE_CHAR '#'
#define BLANK_SQUARE_CHAR '.'

// this defines the width and height of the characters that will appear on the
// screen

// This holds information about our character array that can be used to check
// there is enough space to display it on the bitmap.
typedef struct Character {
  int width;
  int height;
  const int *bitmap_loc;
  char char_representation; //the character the bitmap represents.
} Character;

extern const int ZERO_5X5[5][5];
extern const int ONE_5X5[5][5];
extern const int TWO_5X5[5][5];
extern const int THREE_5X5[5][5];
extern const int FOUR_5X5[5][5];
extern const int FIVE_5X5[5][5];
extern const int SIX_5X5[5][5];
extern const int SEVEN_5X5[5][5];
extern const int EIGHT_5X5[5][5];
extern const int NINE_5X5[5][5];
extern const int COLON_5X5[5][5];

extern const Character one;
extern const Character two;
extern const Character three;
extern const Character four;
extern const Character five;
extern const Character six;
extern const Character seven;
extern const Character eight;
extern const Character nine;
extern const Character colon;

int print_bitmap(int *bitmap_loc);

void add_character_to_bitmap(
    int *bitmap,
    Character character, 
    int start_col, 
    int start_row);

Character create_character(
    int number, 
    int width, 
    int height, 
    const int *bitmap_loc);

int map_bool_to_char(int bitmap_entry);

int get_character_bool_from_position(Character character, int row, int col);

void add_character_to_bitmap(
    int *bitmap,
    Character character, 
    int start_col, 
    int start_row
    );

Character char_to_character_converter(char character);

void update_bitmap_with_string(int *bitmap, char *str);
#endif // !DISPLAY
