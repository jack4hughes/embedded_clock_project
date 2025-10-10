/* This module handles the display features in my testing environment. I
 * designed this to work on mac, no promises that it will work on windows! */


#ifndef BITMAP_DISPLAY_MAC_H
#define BITMAP_DISPLAY_MAC_H

#include <signal.h>
#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "bitmap.h"


//defining how our print statement should look.
#define BLOCK_FULL    "█"    // U+2588
#define BLOCK_DARK    "▓"    // U+2593
#define BLOCK_MEDIUM  "▒"    // U+2592
#define BLOCK_LIGHT   "░"    // U+2591
#define BLOCK_EMPTY   " "

void cleanup_term_io();
// cleans terminal for exit.

void signal_handler(int signum);
//Resets terminal on exit.

int init_term_io();
//initialises screen display.
char *map_pixel_value_to_char(uint16_t bitmap_entry);
/* Provides a mapping that matches pixel values to characters.
 *
 * TODO: Change this to map any uint16_t value to a character.
 */

void clear_screen(); //Clears the terminal output (SLOW)

void cursor_home(); //return the cursor to the home position.

int print_bitmap(uint16_t *bitmap_loc);
/* Prints the bitmap out to the terminal. At the moment, this has no flushing
 * mechanism installed, so the bitmap will just be written below everything
 * else.  */

#endif // !BITMAP_DISPLAY_MAC_H
