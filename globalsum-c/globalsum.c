/**
 * Dylan Bonsell
 * globalsum.c
 * 1/23/2014
**/

#include <stdio.h>
#include <stdlib.h>

/* Global Variables */
int LINELEN = 1024;

/* Prototypes */
void receiveValueFromCore(int n, int value);
void sendValueToCore(int n, int my_x);
void printevencores(int cores);
void printoddcores(int cores);

/**
 * Prints out even cores
 * @param cores
 */
void printevencores(int cores){
	// Variables
	int pos = 0; // Position to write
	char line[LINELEN]; // Current working line
	int corecount = 0; // Current working core
	int steps = 0;

	// Skip first 4 chars
	int i;
	for (i = 0; i < 4; i++){
		line[pos] = ' ';
		pos++;
	}
	// Loop through and make catagories for cores, then print.
	for (i = 0; i < cores; i++){
		sprintf(&line[pos], "%d", corecount);
		sprintf(&line[pos+1], "%d", (i % 10));
		if ((i % 10) == 9)
			corecount++;
		// Skip 2 spaces after each core
		line[pos+2] = ' ';
		line[pos+3] = ' ';
		pos += 4;
	}
	// Print out first line
	line[pos] = '\n';
	line[pos + 1] = '\0';
	printf("%s", line);

	// Now print each step
	pos = 0;


}

/**
 * Prints out odd cores
 * @param cores
 */
void printoddcores(int cores){

}

/**
 * Waits to recieve a value from core n
 * @param n is the core
 * @param value is the value to recieve
 */
void receiveValueFromCore(int n, int value){
	return;
}
/**
 * Sends a value to a core 
 * @param n is the core
 * @param my_x is the value
 */
void sendValueToCore(int n, int my_x){
	return;
}

int 
main(int argc, char **argv){
	// Check for correct arguments
	if (argc != 2){
		printf("You have not entered an argment.\n");
		printf("Please use the format .\\globalsum #cores \n");
		return 1;
	}
	// Variables
	int cores = atoi(argv[1]);


	// Case for even ammount of cores
	if (cores % 2 == 0){
		printevencores(cores);
	}
	// Case for odd ammount
	else{
		printoddcores(cores);
	}

	return 1;
}

