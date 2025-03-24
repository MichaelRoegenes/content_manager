CC = gcc
CFLAGS = -Wall -o
TARGET = content_manager
SOURCES = main.c list_utils.c output_utils.c

OBJECTS = $(SOURCES:.c=.o)

$(TARGET) : $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) $(TARGET)

%.o: %.c list_utils.h output_utils.h
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: clean