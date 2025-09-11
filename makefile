CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = display_test

# Source files:
SOURCES = main.c bitmap_displayer_mac.c bitmap.c time_getter_mac.c
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild
