CC = gcc
CFLAGS = -Isrc -Wall -Wextra -g -lm

# Build and Source File Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Test Directories
UNIT_DIR = unit_tests
TEST_DIR = tests

# Program Build Variables
TARGET = $(BIN_DIR)/my_program
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Test Build Variables
TESTS = $(wildcard $(TEST_DIR)/test_*.c)
TEST_SRCS = $(filter-out $(SRC_DIR)/main.c, $(SRCS))
RUNNER = $(patsubst $(TEST_DIR)/test_%.c, $(UNIT_DIR)/%_test_runner, $(TESTS))

# Default Rule: Build the target executable
all: $(TARGET)

# Link Rule: Combine object files into the final binary
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) -o $@

# Compile Rule: Convert each .c file into a .o file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to create required directories
$(BIN_DIR) $(OBJ_DIR) $(TEST_DIR) $(UNIT_DIR):
	mkdir -p $@

# Test Rule: runs the unit tests
test: $(RUNNER)
$(UNIT_DIR)/%_test_runner: $(TEST_DIR)/test_%.c $(TEST_SRCS) | $(UNIT_DIR)
	$(CC) -Wall -Wextra -g $< $(TEST_SRCS) -o $@ -lm

# Clean Rule: Remove compiled files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	rm -rf $(UNIT_DIR)/

.PHONY: all clean test
