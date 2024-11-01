# Define the compiler
CXX := g++

# Include directories
INCDIR := deps/SDL2/include src

# Library directories
LIBDIR := deps/SDL2/lib

# Compiler flags
CXXFLAGS := $(addprefix -I,$(INCDIR))

# Linker flags
LDFLAGS := -L$(LIBDIR) -lmingw32 -lSDL2main -lSDL2

# Source files
SRC := $(wildcard src/*.cpp) main.cpp

# Object files
OBJ := $(SRC:.cpp=.o)

# Executable name
EXEC := main

# Default target
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $^ -o $@ $(LDFLAGS)

# Rule for object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run target
run: all
	./$(EXEC)

# Clean target
clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all run clean