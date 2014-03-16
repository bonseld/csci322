/**
 * Dylan Bonsel
 *
 * gauss.c
 *
 * runs various solutions to gaussian elimination
 * using openmp
 */

 #include <omp.h>
 #include <stdio.h>
 #include <stdlib.h>

 void row(int A[][], int n);
 void col(int A[][], int n);

 int main(int argc, char **argv){
 	if (argc > 2)
 		omp_set_num_threads(atoi(argv[1])); 
 }

 void row(int A[][], int n){
 	int row, col, local_x;
 	for (row = n-1; row >= 0; row--){
 		local_x = b[row];
 		#pragma omp parallel for reduction(- : local_x)
 		for (col = row+1; col < n; col++){
 			local_x = 
 		}
 	}
 }

 void col(int A[][], int n){

 }
