/* This is the main module that deals with initialising and updating the
 * bitmap. The bitmap is assumed to have constant size.*/

#ifndef DISPLAY
#define DISPLAY

// Including stdint.h -- This holds our type definitions for uint16_t
#include <stdint.h>
// Defining the size of our screen bitmap.
#define CHARACTER_HEIGHT 5
#define CHARACTER_WIDTH 5

#define SCREEN_HEIGHT 32
#define SCREEN_WIDTH 64

// this defines the width and height of the characters that will appear on the
// screen

// This holds information about our character array that can be used to check
// there is enough space to display it on the bitmap.

typedef struct Bitmap {
  uint16_t width;
  uint16_t height;
  uint16_t *bitmap_loc; //This means we have no consts any more! can fix this with unions I think.
} Bitmap;

// These are the locations for our font bitmaps! They need to be stored just like this.
extern const uint16_t BLANK_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH];
extern const uint16_t ZERO_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH];
extern const uint16_t ONE_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH];
extern const uint16_t TWO_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH];
extern const uint16_t THREE_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH];
extern const uint16_t FOUR_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH];
extern const uint16_t FIVE_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH];
extern const uint16_t SIX_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH];
extern const uint16_t SEVEN_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH];
extern const uint16_t EIGHT_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH];
extern const uint16_t NINE_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH];
extern const uint16_t COLON_5X5[CHARACTER_HEIGHT][CHARACTER_WIDTH];

//Defining our bitmap structs.
extern Bitmap character_bitmaps[10];
extern Bitmap colon;
extern Bitmap blank;

//define screen here!
extern uint16_t screen_bitmap_array[SCREEN_HEIGHT][SCREEN_WIDTH];
extern Bitmap screen_bitmap;

//This function shoould initialise all the characters we have designed.
void init_fonts(void);

void overlay_bitmaps(
    Bitmap *underlay_bitmap,
    Bitmap overlay_bitmap, 
    uint16_t start_col, 
    uint16_t start_row);

Bitmap create_bitmap(
    uint16_t width, 
    uint16_t height, 
    const uint16_t *bitmap_loc);

uint16_t get_character_bool_from_position(Bitmap character, 
    uint16_t row, 
    uint16_t col);

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
    uint16_t start_row, 
    uint16_t start_col
    );

void init_characters(void);
/* initialises character array using create_character function.*/

void init_screen_bitmap(void);
/* This function intialises our screen.*/
#endif // !DISPLAY
