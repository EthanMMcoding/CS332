# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -lpthread

# Target executable
TARGET = hw4

# Source files
SRC = hw4.c

# Default rule to build the executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

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