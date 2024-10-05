CC = gcc

CFLAGS = -Wall -g

TARGET = hw2

SRC = Homework02.c

HDRS = traverse.h file_struct.h sort.h

$(TARGET): $(SRC) $(HDRS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET) $(ARGS)

clean:
	rm -f $(TARGET)