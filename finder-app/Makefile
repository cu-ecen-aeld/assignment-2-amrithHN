CC = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -Werror -std=c11 -g
TARGET = writer
SOURCES = writer.c
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean