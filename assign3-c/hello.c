/**
 * Dylan Bonsell
 * Part 1 of 3
 * Centralized Solution
 */

#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

#define send_data_tag 2001
#define return_data_tag 2002

main(int argc, char **argv)
   {
      int my_id, root_process, ierr, num_procs, an_id, partial_sum, sum, sender;
      int p = 100; // Number of iterations
      MPI_Status status;
      ierr = MPI_Init(&argc, &argv);
      /* find out MY process ID, and how many processes were started. */
      ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
      ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
      int i;
      for(i=0; i < p; i++){
         if(my_id != 0) {
            /* do this work in any remaining processes */
            unsigned int seed = my_id;
            int myrand = rand_r(&seed) % 100;
            ierr = MPI_Send(&myrand, 1, MPI_INT, 0, send_data_tag, MPI_COMM_WORLD); 
         }
      }
      for(an_id = 1; an_id < num_procs; an_id++) {
            ierr = MPI_Recv( &partial_sum, 1, MPI_LONG, MPI_ANY_SOURCE,
                  return_data_tag, MPI_COMM_WORLD, &status);
            sender = status.MPI_SOURCE;

            printf("Partial sum %i returned from process %i\n", partial_sum, sender);
     
            sum += partial_sum;
         }
         /* Stop this process */
      ierr = MPI_Finalize();
   }
