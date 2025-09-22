#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "bitmap.h"

// DEFINING FOR COMPILE-TIME.
// We're using 5-bit colour for red and blue, and 6-bit colour for green.
#define RED_BITSHIFT 11
#define GREEN_BITSHIFT 5
#define BLUE_BITSHIFT 0

//setting up row lengths:
#define ROW_LENGTH 64
#define ROWS_IN_REGISTER 2

/* These macros calculate the size of the buffer from ROW_LENGTH and
 * ROWS_IN_REGISTER. The display buffer should always exist, so this avoids any
 * malloc and free calls.*/

#define BUFFER_SIZE_BITS (ROWS_IN_REGISTER * ROW_LENGTH)
#define BUFFER_SIZE_UINT64_T ((BUFFER_SIZE_BITS + 63) /64) //the +63 here makes sure that our array isnt one entr short.
extern uint64_t red_row_buffer[BUFFER_SIZE_UINT64_T];
extern uint64_t blue_row_buffer[BUFFER_SIZE_UINT64_T];
extern uint64_t green_row_buffer[BUFFER_SIZE_UINT64_T];

bool get_color_value(uint16_t value, int iteration, int color_bitshift);
// gets the value of a specific colour on a specific iteration. Outputs a boolean value.

int write_to_row_buffer(int iteration, int row_number, Bitmap pixelmap,
                        uint64_t *buffer_loc);  
// Writes to the row data buffer from a bitmap.

int send_row_buffer(uint64_t *buffer_loc);
// Sends the row data out to the display, then displays it.

int clear_row_buffer(uint64_t * buffer_loc);
// clears all data currently in the row data buffer.
