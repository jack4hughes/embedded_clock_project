#include <string.h>
#include <stdio.h>
#include "page.h"

int append_to_buffer(char *string_start_pos);

void display_input(InputButtonTypes input);

void display_edit_mode(EditTimeState edit_mode);

void display_current_page(ClockMode *mode);

void display_current_mode(int mode); //This is an int because different pages have different modes.

int print_buffer();

int flush_buffer();
