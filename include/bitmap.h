/* This is the main module that deals with initialising and updating the
 * bitmap. The bitmap is assumed to have constant size.*/

#ifndef DISPLAY
#define DISPLAY

// Including stdint.h -- This holds our type definitions for uint8_t
#include <stdint.h>
// Defining the size of our screen bitmap.
#define CHARACTER_HEIGHT 5
#define CHARACTER_WIDTH 5

#define SCREEN_HEIGHT 5
#define SCREEN_WIDTH 60

// this defines the width and height of the characters that will appear on the
// screen

// This holds information about our character array that can be used to check
// there is enough space to display it on the bitmap.

typedef struct Bitmap {
  uint8_t width;
  uint8_t height;
  uint8_t *bitmap_loc; //This means we have no consts any more! can fix this with unions I think.
} Bitmap;

// These are the locations for our font bitmaps! They need to be stored just like this.
extern const uint8_t BLANK_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH];
extern const uint8_t ZERO_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH];
extern const uint8_t ONE_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH];
extern const uint8_t TWO_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH];
extern const uint8_t THREE_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH];
extern const uint8_t FOUR_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH];
extern const uint8_t FIVE_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH];
extern const uint8_t SIX_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH];
extern const uint8_t SEVEN_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH];
extern const uint8_t EIGHT_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH];
extern const uint8_t NINE_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH];
extern const uint8_t COLON_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH];

//Defining our bitmap structs.
extern Bitmap character_bitmaps[10];
extern Bitmap colon;
extern Bitmap blank;

//define screen here!
extern uint8_t screen_bitmap_array[SCREEN_HEIGHT][SCREEN_WIDTH];
extern Bitmap screen_bitmap;

//This function shoould initialise all the characters we have designed.
void init_fonts(void);

void overlay_bitmaps(
    Bitmap *underlay_bitmap,
    Bitmap overlay_bitmap, 
    uint8_t start_col, 
    uint8_t start_row);

Bitmap create_bitmap(
    uint8_t width, 
    uint8_t height, 
    const uint8_t *bitmap_loc);

uint8_t get_character_bool_from_position(Bitmap character, 
    uint8_t row, 
    uint8_t col);

/* Returns a string from a character lookup. Currently handled using a switch
 * statement (but this is dumb.)
 *
 * TODO: Need to rename this to character_bitmap_lookup.
 */
Bitmap get_character_bitmap(char character);

/* Appends a string to a bitmap in the specified location. Need to test what
*  happens when this location is outside of bounds */
void update_bitmap_with_string(
    Bitmap *bitmap, 
    char *str_ptr, 
    uint8_t start_row, 
    uint8_t start_col
    );

void init_characters(void);
/* initialises character array using create_character function.*/

void init_screen_bitmap(void);
/* This function intialises our screen.*/
#endif // !DISPLAY
