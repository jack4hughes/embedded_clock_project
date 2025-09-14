/* This module handles the display features in my testing environment. I
 * designed this to work on mac, no promises that it will work on windows! */


#ifndef BITMAP_DISPLAY_MAC_H
#define BITMAP_DISPLAY_MAC_H

#include "bitmap.h"
#include <stdio.h>


//defining how our print statement should look.
#define FULL_SQUARE_CHAR '#'
#define BLANK_SQUARE_CHAR ' '

char map_bool_to_char(uint8_t bitmap_entry);
/* Provides a mapping that matches bools to characters.
 * IE 0101011 becomes ' # # ##' if 0 maps to ' ' and 1 maps to '#'
 *
 * TODO: Change this to map any uint8_t value to a character.
 */

int print_bitmap(uint8_t *bitmap_loc);
/* Prints the bitmap out to the terminal. At the moment, this has no flushing
 * mechanism installed, so the bitmap will just be written below everything
 * else.  */

#endif // !BITMAP_DISPLAY_MAC_H
