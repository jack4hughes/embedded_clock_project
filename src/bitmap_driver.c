#include "bitmap_driver.h"

uint64_t red_row_buffer[BUFFER_SIZE_UINT64_T] = {0}; //initialises pixel_row_buffer.
uint64_t blue_row_buffer[BUFFER_SIZE_UINT64_T] = {0};
uint64_t green_row_buffer[BUFFER_SIZE_UINT64_T] = {0};

bool get_color_value(uint16_t value, int iteration, int color_bitshift) {
  bool output = value >> color_bitshift >> iteration && 1;
  return output;
}
// gets the value of a specific colour on a specific iteration. Outputs a boolean value.

int write_to_row_buffer(int iteration, int row_number, Bitmap pixelmap,
                        uint64_t *buffer_loc) {
  uint64_t col_number = 0;
  int buffer_number_position = 0;

  while (col_number < BUFFER_SIZE_BITS) {
    uint16_t *pixel_loc = pixelmap.bitmap_loc + pixelmap.width * row_number + col_number;
    uint16_t pixel = *pixel_loc;

    
    bool red = get_color_value(pixel, iteration, RED_BITSHIFT);
    bool green = get_color_value(pixel, iteration, GREEN_BITSHIFT);
    bool blue = get_color_value(pixel, iteration, BLUE_BITSHIFT);
    
    red_row_buffer[buffer_number_position] += (uint64_t)(red << col_number);
    blue_row_buffer[buffer_number_position] += (uint64_t)(blue << col_number);
    green_row_buffer[buffer_number_position] += (uint64_t)(green << col_number);
    
    if ((col_number % 64 == 0) && (col_number > 0)) {
      buffer_number_position++;
    }
  }  
} 
// Writes to the row data buffer from a bitmap.

int send_row_buffer(uint64_t *buffer_loc);
// Sends the row data out to the display, then displays it.

int clear_row_buffer(uint64_t * buffer_loc);
// clears all data currently in the row data buffer.
