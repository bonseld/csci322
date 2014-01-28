
CC=gcc
CFLAGS=-g -c -Wall 
LDFLAGS=
SOURCES=distsum.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=distsum

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ -lm

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o $(EXECUTABLE)
