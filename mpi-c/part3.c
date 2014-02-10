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
 MPI_Request request;
 int iterations = 100; 
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
      seed = (unsigned)time(NULL)+my_id*num_procs*i + name_len;
      partial_max = rand_r(&seed)%500000+1;
      for(an_id = 1; an_id < num_procs; an_id++) {
        if (an_id != my_id)
          ierr = MPI_Isend( &partial_max, 1, MPI_LONG, an_id, return_data_tag, MPI_COMM_WORLD, &request);
        }
      
      for(an_id = 1; an_id < num_procs; an_id++) {
        if (an_id != my_id){
          ierr = MPI_Irecv( &partial_max, 1, MPI_LONG, an_id ,return_data_tag, MPI_COMM_WORLD, &request);
          if(partial_max > max)
            max = partial_max;
        }
    }
  }








  
  MPI_Barrier(MPI_COMM_WORLD); // Blocks to get Wtime
  end = MPI_Wtime(); // Get end time
  ierr = MPI_Finalize(); // Close MPI
  /* Print the time taken if root_process*/
  if(my_id == root_process) 
      printf("The time spent was %f seconds\n", end-begin);
}

  tag = 201;
  next = (rank + 1) % size;
  from = (rank + size - 1) % size;





if (rank == 0) {
    printf("Enter the number of times around the ring: ");
    num = 1

    printf("Process %d sending %d to %d\n", rank, num, next);
    MPI_Send(&num, 1, MPI_INT, next, tag, MPI_COMM_WORLD); 
  }

  while (1) {

    MPI_Recv(&num, 1, MPI_INT, from, tag, MPI_COMM_WORLD, &status);
    printf("Process %d received %d\n", rank, num);

    if (rank == 0) {
      num--;
      printf("Process 0 decremented num\n");
    }

    printf("Process %d sending %d to %d\n", rank, num, next);
    MPI_Send(&num, 1, MPI_INT, next, tag, MPI_COMM_WORLD);

    if (num == 0) {
      printf("Process %d exiting\n", rank);
      break;
    }
  }

  /* The last process does one extra send to process 0, which needs */
  /* to be received before the program can exit */

  if (rank == 0)
    MPI_Recv(&num, 1, MPI_INT, from, tag, MPI_COMM_WORLD, &status);