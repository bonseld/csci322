CC = gcc
SOURCES = raytrace.c vectors.c
OBJECTS = $(SOURCES:.c=.o)
TESTSOURCES = AllTests.c CuTest.c testvectors.c testraytrace.c
TESTOBJECTS = $(TESTSOURCES:.c=.o)

CFLAGS = -c -Wall
LDFLAGS = -lm 

test: $(OBJECTS) $(TESTOBJECTS)
	$(CC) $(OBJECTS) $(TESTOBJECTS) $(LDFLAGS) -g -o test
random: $(OBJECTS) randomspheres.o
	$(CC) $(OBJECTS) randomspheres.o $(LDFLAGS) -g -o random
ring: $(OBJECTS) ring.o
	$(CC) $(OBJECTS) ring.o $(LDFLAGS) -o ring
.c.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	clear
	rm -rf *o $(EXECUTABLE)

