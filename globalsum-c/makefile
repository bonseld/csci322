
CC=gcc
CFLAGS=-g -c -Wall
LDFLAGS=
SOURCES=globalsum.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=globalsum

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	clear
	rm -rf *o $(EXECUTABLE)
