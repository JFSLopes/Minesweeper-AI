# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -Wextra -g -std=c++17

# Frameworks needed for Core Graphics
FRAMEWORKS = -framework ApplicationServices

# Source and build directories
SRC_DIR = src
BUILD_DIR = build

# Find all source files in the src directory
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)

# Generate object file paths in the build directory
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Output executable
TARGET = minesweeper

# Default target
all: $(TARGET)

# Link object files to create the executable, including frameworks
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(FRAMEWORKS)

# Compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure the build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean up build and output files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean