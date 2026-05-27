# Compiler and Flags
CC = gcc
CFLAGS = -Isrc -Wall -Wextra -g

# Directory Definitions
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# File Definitions
TARGET = $(BIN_DIR)/my_program
# Automatically find all .c files in the src folder
SRCS = $(wildcard $(SRC_DIR)/*.c)
# Convert the list of .c files to a list of .o files in the obj folder
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default Rule: Build the target executable
all: $(TARGET)

# Link Rule: Combine object files into the final binary
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) -o $@

# Compile Rule: Convert each .c file into a .o file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to create required directories
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Clean Rule: Remove compiled files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
