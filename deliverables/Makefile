# Define compiler
CXX=g++

# Define compiler flags
CXXFLAGS=-std=c++20

# Define the source file
SRC=E6-code-examples.cpp

# Define the output directory and executable name
OUTDIR=./output
EXECUTABLE=$(OUTDIR)/program

# Default target
all: clean build run

# Clean the output directory
clean:
	rm -rf $(OUTDIR)

# Build the program
build:
	mkdir -p $(OUTDIR)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXECUTABLE)

# Run the program
run:
	$(EXECUTABLE)

# Phony targets for non-file targets
.PHONY: clean build run all
