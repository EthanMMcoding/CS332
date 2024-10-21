# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Target executable
TARGET = hw3

# Source files
SRC = hw3.c word_counter.c traverse.c

# Object files (generated from source files)
OBJ = $(SRC:.c=.o)

# Header files
HEADERS = word_counter.h traverse.h

# Default rule to build the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Rule to compile .c files into .o files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -f $(OBJ) $(TARGET)

# Convenience rule to run the program
run: $(TARGET)
	./$(TARGET) $(ARGS)

# Phony targets
.PHONY: clean run