# Compiler and Flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.

# Build Directory
BUILD_DIR = build

# Target executable
TARGET = $(BUILD_DIR)/iron-nexus

# Find all source files recursively
SRCS = $(shell find . -name "*.cpp")

# Map source files to object files in the build directory
# e.g., Railway/src/Station.cpp -> build/Railway/src/Station.o
OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

# Default rule
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files to object files
# mkdir -p ensures the subdirectory structure exists within build/
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Phony targets
.PHONY: all clean
