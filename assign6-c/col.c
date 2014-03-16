/**
 * Dylan Bonsel
 *
 * col.c
 *
 * runs various solutions to gaussian elimination
 * using openmp
 */

 #include <omp.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>


 int main(int argc, char **argv){
 	int n, i, j, row, col;
 	double begin, end, time_spent;
 	begin = clock();
 	if (argc > 2)
 		omp_set_num_threads(atoi(argv[1])); 
 	n = 10000;
 	int x[n];
 	int A[n][n];
 	for (i = 0; i < n; i++){
 		for (j= 0; j < n; j++){
 			A[i][j] = 1;
 		}
 	}

 	int b[n];
 	for (i = 1; i < n+1; i++)
 		b[i-1] = i;

 	for (row = 0; row < n; row++)
 		x[row] = b[row];

 	for (col = n-1; col >= 0; col--){
 		x[col] /= A[col][col];
 		#pragma omp parallel for schedule(dynamic) 
 		for (row = 0; row < col; row++)
 			x[row] -= A[row][col]*x[col];
 	}
 	end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f\n", time_spent);
 	return 1;
 }

