#=============================================================================
# Makefile for a C++ application using wxWidgets and MariaDB Connector/C++.
# This file handles the linking and compilation for a cross-platform setup.
#=============================================================================

# The name of your executable.
EXECUTABLE = my_crm_app

# The main source file.
SOURCES = main.cpp

# Use wx-config to get compiler flags and linker libraries for wxWidgets.
# We also include --unicode=yes and --static=yes for a static Unicode build.
# This makes the application more portable.
WX_CFLAGS := $(shell wx-config --cxxflags --unicode=yes --static=yes)
WX_LIBS := $(shell wx-config --libs --unicode=yes --static=yes)

# Use mysql_config or mariadb_config to get the flags for the database connector.
# On some systems, it might be mariadb_config.
# You might need to change this if your system uses a different utility.
DB_CFLAGS := $(shell mysql_config --cflags)
DB_LIBS := $(shell mysql_config --libs)

# The C++ compiler to use.
CXX = g++

# Final flags for compilation and linking.
CXXFLAGS = $(WX_CFLAGS) $(DB_CFLAGS) -std=c++11 -Wall
LDFLAGS = $(WX_LIBS) $(DB_LIBS)

#=============================================================================
# The main build rule.
#=============================================================================
all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	@echo "Compiling and linking..."
	$(CXX) $(SOURCES) $(CXXFLAGS) $(LDFLAGS) -o $(EXECUTABLE)
	@echo "Build complete. Run with: ./$(EXECUTABLE)"

#=============================================================================
# Clean rule.
#=============================================================================
clean:
	@echo "Cleaning up..."
	@rm -f $(EXECUTABLE)
	@echo "Done."

.PHONY: all clean

