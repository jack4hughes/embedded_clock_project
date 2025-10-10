#include "bitmap_displayer_mac.h"

static struct termios standard_termios;
static int terminal_modified = 0;

void signal_handler(int signum) {
  cleanup_term_io();
  exit(signum);
}

void cleanup_term_io() {
  // Restore original terminal settings
  tcsetattr(STDIN_FILENO, TCSANOW, &standard_termios);
  
  printf("\033[?25h");  // Show cursor
  printf("\033[0m");    // Reset colors/formatting
  fflush(stdout);
}

void clear_screen() {
  printf("\033[2J\033[H");
  fflush(stdout);
}

int init_term_io() {
  init_fonts(); //initialises the fonts in memory. 
  init_screen_bitmap(); //initialises the screen bitmap within memory.
  clear_screen();
  
  // Save current terminal settings
  tcgetattr(STDIN_FILENO, &standard_termios);
  
  // Set up non-canonical mode
  struct termios new_termios = standard_termios;
  new_termios.c_lflag &= ~(ICANON | ECHO);
  new_termios.c_cc[VMIN] = 0;
  new_termios.c_cc[VTIME] = 2;  // This is being used as our frequency. can only do 10FPS.
  tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
 
  setvbuf(stdout, NULL, _IONBF, 0); //makes sure that we are not writing to terminal buffer.
  signal(SIGINT, signal_handler);
  atexit(cleanup_term_io); //resets the terminal when we exit.
  
  return 0;
}


void hide_cursor() {
  printf("\033[?25l");
}

void show_cursor() {
  
}
void cursor_home() {
  printf("\033[H");
  fflush(stdout);
} //Clears the terminal output (SLOW)


char *map_pixel_value_to_char(uint16_t character_entry) {
  if (character_entry == 0) {
    return BLOCK_EMPTY;
  }
  else if (character_entry < 64) {
    return BLOCK_LIGHT;
  }
  else if (character_entry < 128) {
    return BLOCK_MEDIUM;
  }

  else if (character_entry < 192) {
    return BLOCK_DARK; 
  }

  else if (character_entry == 255) {
    return BLOCK_FULL;
  }

  else {
    return BLOCK_EMPTY;
  }
}


int print_bitmap(uint16_t *bitmap_loc) {
  // Prints the current bitmap out to the screen.
  int i = 0;
  int col_number = 0;
  hide_cursor();
  cursor_home(); //should send the cursor home?
  
  while (i < SCREEN_HEIGHT * SCREEN_WIDTH) {
  col_number = i % SCREEN_WIDTH;
    uint16_t *current_position = bitmap_loc + i;
    uint16_t current_pixel_value = *current_position;
    char * current_char = map_pixel_value_to_char(current_pixel_value);
    printf("%s", current_char);
    i++;
    if (col_number == SCREEN_WIDTH - 1) {  // End of row
        printf("\n");
    }; 
  }
  return 0;  // confirms that operation has been completed.
}

