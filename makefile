#=============================================================================
# Makefile for a C++ application using wxWidgets and MariaDB Connector/C++.
# This version supports a separate build directory.
#
# Created by Gemini to support a project structure with a 'src' folder
# for sources and a 'build' folder for compiled objects and executable.
#
# Updated to use shared wxWidgets libraries to avoid static build warnings.
# Now includes a fix to create subdirectories within the build folder.
#=============================================================================

# --- Project Configuration ---
# The name of your executable.
EXECUTABLE = ciarem_exec

# The build and source directories.
BUILD_DIR = build
SRC_DIR = src

# Automatically find all C++ source files in the source directory and its subdirectories.
# This ensures new files are automatically included in the build process.
SOURCES = $(shell find $(SRC_DIR) -name "*.cpp")

# Create a list of object files from the source files, placing them in the build directory.
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

# --- Compiler and Linker Flags ---
# The C++ compiler to use.
CXX = g++

# Use wx-config to get compiler flags and linker libraries for wxWidgets.
# We include --unicode=yes for a Unicode build, but remove --static=yes.
WX_CFLAGS := $(shell wx-config --cxxflags --unicode=yes)
WX_LIBS := $(shell wx-config --libs --unicode=yes)

# Use mysql_config or mariadb_config to get the flags for the database connector.
DB_CFLAGS := $(shell mysql_config --cflags)
DB_LIBS := $(shell mysql_config --libs)

# Final flags for compilation and linking.
CXXFLAGS = $(WX_CFLAGS) $(DB_CFLAGS) -std=c++11 -Wall
LDFLAGS = $(WX_LIBS) $(DB_LIBS)

# VPATH tells Make where to find source files.
# This makes it easier for Make to find the dependencies.
VPATH = $(SRC_DIR):$(SRC_DIR)/frames:$(SRC_DIR)/libs

# --- Build Rules ---
# The default rule. Builds the project by first creating the build directory.
all: $(BUILD_DIR) $(BUILD_DIR)/$(EXECUTABLE)
	@echo "Build complete. Executable is in the 'build' directory."

# Rule to create the build directory if it doesn't exist.
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# The rule for the final executable. It depends on all object files.
$(BUILD_DIR)/$(EXECUTABLE): $(OBJECTS)
	@echo "Linking..."
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@
	@echo "Executable created: $@"

# Generic rule to compile a .cpp file into a .o object file.
# The `$<` refers to the first prerequisite (the .cpp file).
# The `$@` refers to the target (the .o file).
# The new `$(dir $@)` part extracts the directory from the output path.
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling $< -> $@"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# --- Utility Rules ---
# Clean rule to remove the build directory and its contents.
clean:
	@echo "Cleaning up..."
	@rm -rf $(BUILD_DIR)
	@echo "Done."

# Run rule to execute the program from the build directory.
run: all
	@echo "Running the application..."
	./$(BUILD_DIR)/$(EXECUTABLE)

.PHONY: all clean run
