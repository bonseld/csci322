/**
 * Dylan Bonsell
 * part1.c
 * Implements the centralized solution to find the max,
 * then prints out the time it takes to complete.
 */

 #include <mpi.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>

 #define return_data_tag 2002

int main(int argc, char **argv)
{
/* Variables */
 double begin, end; // Timing Variables
 int my_id, root_process, ierr, num_procs, an_id, sender, name_len;
 char processor_name[MPI_MAX_PROCESSOR_NAME]; // Temp to generate seed
 long int partial_max, max; 
 unsigned int seed; 
 MPI_Status status;
 int iterations = 10000; 
 root_process = 0;
 ierr = MPI_Init(&argc, &argv); // Start MPI
 MPI_Barrier(MPI_COMM_WORLD); // Blocks to get Wtime 
 begin = MPI_Wtime(); // Start Time
 MPI_Get_processor_name(processor_name, &name_len); // Get the processor time to add to seed
 int i;
 for(i = 0; i < iterations; i++){
   max = 0;
   /* Initialization of MPI */
   ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
   ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
     /* Process 0 */
     if(my_id == root_process) {
      for(an_id = 1; an_id < num_procs; an_id++) {
        ierr = MPI_Recv( &partial_max, 1, MPI_LONG, MPI_ANY_SOURCE,return_data_tag, MPI_COMM_WORLD, &status);
        if(partial_max > max)
          max = partial_max;
      }
    }
    /* All other processes */
    else {
      seed = (unsigned)time(NULL)+my_id*num_procs*i + name_len;
      partial_max = rand_r(&seed)%500000+1;
      ierr = MPI_Send( &partial_max, 1, MPI_LONG, root_process, return_data_tag, MPI_COMM_WORLD);
    }
  }
  MPI_Barrier(MPI_COMM_WORLD); // Blocks to get Wtime
  end = MPI_Wtime(); // Get end time
  ierr = MPI_Finalize(); // Close MPI
  /* Print the time taken if root_process*/
  if(my_id == root_process) 
      printf("The time spent was %f seconds\n", end-begin);
}