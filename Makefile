# AI Generated Makefile
# So much easier than writing your own

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wpedantic -Werror

# Directories
SRC_DIR = src
BUILD_DIR = build
LIB_DIR = lib
DRIVER_DIR = driver
TEST_DIR = tests

# Static library name
LIB_NAME = queues
STATIC_LIB = $(LIB_DIR)/lib$(LIB_NAME).a

# Recursively find all cpp files in src
SOURCES := $(shell find $(SRC_DIR) -name '*.cpp')

# Map src/.../*.cpp → build/.../*.o
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Driver
DRIVER_SRC = $(DRIVER_DIR)/driver.cpp
DRIVER_OBJ = $(BUILD_DIR)/driver.o
DRIVER_EXEC = $(BUILD_DIR)/driver_program

# Tests
TEST_SOURCES := $(shell find $(TEST_DIR) -name '*.cpp')
TEST_OBJECTS := $(TEST_SOURCES:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/tests/%.o)
TEST_EXECS := $(TEST_SOURCES:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/tests/%)

# Default target (build everything)
all: lib driver tests

# Create static library
lib: $(STATIC_LIB)

$(STATIC_LIB): $(OBJECTS)
	ar rcs $@ $^

# Link driver program
driver: $(DRIVER_EXEC)

$(DRIVER_EXEC): $(DRIVER_OBJ) $(STATIC_LIB)
	$(CXX) $(DRIVER_OBJ) $(STATIC_LIB) -o $@

# Link tests (one for each source file in tests)
tests: $(TEST_EXECS)

# Compile src files (with subdirectories)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile driver
$(BUILD_DIR)/driver.o: $(DRIVER_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile test files
$(BUILD_DIR)/tests/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link individual test binaries
$(BUILD_DIR)/tests/%: $(BUILD_DIR)/tests/%.o $(STATIC_LIB)
	$(CXX) $^ -o $@

# Clean
clean:
	rm -rf $(BUILD_DIR) $(STATIC_LIB)

.PHONY: all lib driver tests clean
