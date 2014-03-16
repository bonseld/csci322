/**
 * Dylan Bonsel
 *
 * row.c
 *
 * runs various solutions to gaussian elimination
 * using openmp
 */

 #include <omp.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>


 int main(int argc, char **argv){
 	int n, i, j, row, col, local_x;
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

 	for (row = n-1; row >= 0; row--){
 		local_x = b[row];
 		#pragma omp parallel for schedule(dynamic) reduction(- : local_x)
 		for (col = row+1; col < n; col++){
 			local_x = A[row][col]*x[col];
 		}
 		x[row] = local_x;
 		x[row] /= A[row][row];
 	}
 	end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f\n", time_spent);
 	return 1;
 }

