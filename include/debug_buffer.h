#include <string.h>
#include <stdio.h>
#include "page.h"

int append_to_buffer(char *string_start_pos);

void write_input(InputButtonTypes input);

void write_edit_mode(EditTimeState edit_mode);

void write_current_page(ClockMode *mode);

void write_current_mode(int mode); //This is an int because different pages have different modes.

int print_buffer();

int flush_buffer();
