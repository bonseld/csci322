/**
 * Dylan Bonsell
 * globalsum.c
 * 1/23/2014
**/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Global Variables */
int LINELEN = 1024;

/* Prototypes */
void printcores(int cores);

// Prints Cores
void printcores(int cores){
	// Variables
	int pos = 0; // Position to write
	char line[LINELEN]; // Current working line
	int step = 0; // Current step
	int laststep = 0; //Flag for last step
	int sr = 0; // Bitwise operator to tell if sending or recieving core

	// Skip first 4 chars
	int i;
	for (i = 0; i < 4; i++){
		line[pos] = ' ';
		pos++;
	}
	// Loop through and make catagories for cores, then print.
	for (i = 0; i < cores; i++){
		sprintf(&line[pos], "%02d", i);
		line[pos+2] = ' ';
		line[pos+3] = ' ';
		pos += 4;
	}
	// Print out first line
	line[pos] = '\n';
	line[pos + 1] = '\0';
	printf("%s", line);

	// Now print each step
	while(!laststep){
		pos = 0;
		sprintf(&line[pos], "%02d", step);
		line[pos+2] = ' ';
		pos += 3;
		for(i = 0; i < cores; i++){
			// Determine if the core is being used
			if ((i % ((int) pow(2,step))) == 0){
				if (sr && (i-((int) pow(2,step))) < cores && (i-((int) pow(2,step))) >= 0){
					sprintf(&line[pos], "S%02d", (i-((int) pow(2,step))));
					sr = 0;
				}
				else if ((i+((int) pow(2,step))) < cores){
					sprintf(&line[pos], "R%02d", (i+((int) pow(2,step))));
					sr = 1;
				}
				else
					sprintf(&line[pos], "   ");
				line[pos+3] = ' ';
				pos += 4;
			}
			else{
				sprintf(&line[pos], "   ");
				line[pos+3] = ' ';
				pos += 4;
			}
		}
		line[pos] = '\n';
		line[pos + 1] = '\0';
		printf("%s", line);
		if ((((int) pow(2,step))) >= (cores / 2))
			laststep = 1;
		step++;
	}
}

void receiveValueFromCore(int n, int value){
	return;
}

void sendValueToCore(int n, int my_x){
	return;
}

int main(int argc, char **argv){
	// Check for correct arguments
	if (argc != 2){
		printf("You have not entered an argment.\n Please use the format .\\distsum #cores \n");
		return 1;
	}
	// Variables
	int cores = atoi(argv[1]);
	// Print Algo
	printcores(cores);
	return 1;
}

