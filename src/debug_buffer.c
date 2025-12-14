#include "debug_buffer.h"
#include <stdarg.h>
#include <stdio.h>

#define MAX_BUFFER_LENGTH 1024
#define BUFFER_LINE_LENGTH 100
#define BUFFER_LINE_NUMBER 15`1`

/* Desired behavhior:
 * x lines at bottom of screen.
* Some lines (current mode, edit mode, countdown edit mode) need to be constant (maybe model these as seperate buffers?)
* Some lines form a deque.
*
* solution: list of pointers to lines.
*
*/

// might be a nicer way to define this!
char current_page_buffer[BUFFER_LINE_LENGTH] = {'\0'}; //writes 0s to buffer.
char current_mode_buffer[BUFFER_LINE_LENGTH] = {'\0'}; //writes 0s to buffer.
char current_edit_mode_buffer[BUFFER_LINE_LENGTH] = {'\0'}; //writes 0s to buffer.

// The rest of the buffer lines are a ring buffer.
char buffer_line_0[BUFFER_LINE_LENGTH] = {0}; //writes 0s to buffer.
char buffer_line_1[BUFFER_LINE_LENGTH] = {0}; //writes 0s to buffer.
char buffer_line_2[BUFFER_LINE_LENGTH] = {0}; //writes 0s to buffer.
char buffer_line_3[BUFFER_LINE_LENGTH] = {0}; //writes 0s to buffer.
char buffer_line_4[BUFFER_LINE_LENGTH] = {0}; //writes 0s to buffer.
char buffer_line_5[BUFFER_LINE_LENGTH] = {0};//writes 0s to buffer.
char buffer_line_6[BUFFER_LINE_LENGTH] = {0};//writes 0s to buffer.
char buffer_line_7[BUFFER_LINE_LENGTH] = {0}; //writes 0s to buffer.
char buffer_line_8[BUFFER_LINE_LENGTH] = {0}; //writes 0s to buffer.
char buffer_line_9[BUFFER_LINE_LENGTH] = {0}; //writes 0s to buffer.
char buffer_line_a[BUFFER_LINE_LENGTH] = {0}; //writes 0s to buffer.
char buffer_line_b[BUFFER_LINE_LENGTH] = {0}; //writes 0s to buffer.
char buffer_line_c[BUFFER_LINE_LENGTH] = {0}; //writes 0s to buffer.
char buffer_line_d[BUFFER_LINE_LENGTH] = {0}; //writes 0s to buffer.
char buffer_line_e[BUFFER_LINE_LENGTH] = {0}; //writes 0s to buffer.
char buffer_line_f[BUFFER_LINE_LENGTH] = {0}; //writes 0s to buffer.

char *input_ring_buffer[16] = {
  buffer_line_0, buffer_line_1, buffer_line_2, buffer_line_3, 
  buffer_line_4, buffer_line_5, buffer_line_6, buffer_line_7,
  buffer_line_8, buffer_line_9, buffer_line_a, buffer_line_b,
  buffer_line_c, buffer_line_d, buffer_line_e, buffer_line_f}; //A buffer that stores the first character of each line.

unsigned int input_ring_buffer_entry_index = 0;

void write_line(char *buffer, const char *format, ...) {
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, BUFFER_LINE_LENGTH, format, args);
  va_end(args);
}

void write_current_page(ClockMode *page) {
  write_line(current_page_buffer, "page:\t\t%p", page);  
}

void write_current_mode(int mode) {
  write_line(current_mode_buffer, "mode:\t\t%d", mode);
}

void write_edit_mode(EditTimeState edit_mode) {
  write_line(current_edit_mode_buffer, "edit mode:\t%d", edit_mode);
}

void write_input(InputButtonTypes input) {
  char *buffer = input_ring_buffer[input_ring_buffer_entry_index]; //gets the right buffer_line_1
  switch(input) {
    case MODE_BUTTON: write_line(buffer, "mode"); break;
    case EDIT_BUTTON: write_line(buffer, "edit"); break;
    case SNOOZE_BUTTON: write_line(buffer, "snooze"); break; 
    case UP_BUTTON: write_line(buffer, "up"); break;
    case DOWN_BUTTON: write_line(buffer, "down"); break;
  }
  //clean wrapping for ring buffer.
  input_ring_buffer_entry_index = (input_ring_buffer_entry_index + 1) % 16;
}

int print_buffer() {
  puts(current_page_buffer);
  puts(current_mode_buffer);
  puts(current_edit_mode_buffer);

  int i;
  for(int i = 0; i<16; i++) {
    unsigned int current_buffer_index = (input_ring_buffer_entry_index - i + 16) % 16;
    char *current_string = input_ring_buffer[current_buffer_index];
    puts(current_string);
  }
  return 0;
}

int flush_buffer() {
  int current_buffer_position = 0;
  return 0;
}
