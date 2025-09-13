# Defining Directories.
SOURCE_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Select Compiler.
CC = gcc

# Add Compiler Flags:
CFLAGS = -Wall -Wextra -std=c99 -I$(INCLUDE_DIR)

# Tell the code where to write the executable.
TARGET = $(BUILD_DIR)/display_test

# Find source files and map them to build directory
SOURCES = $(wildcard $(SOURCE_DIR)/*.c)
OBJECTS = $(patsubst $(SOURCE_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

all: $(TARGET)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJECTS) | $(BUILD_DIR)
	$(CC) $(OBJECTS) -o $(TARGET)

# Pattern rule: compile .c files from src/ to .o files in build/
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all

.PHONY: all clean rebuild
