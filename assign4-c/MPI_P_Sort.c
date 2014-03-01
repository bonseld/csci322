/**
 * Dylan Bonsell
 * MPI_P_Sort.c
 *
 * Sorts an array using sequential sort 
 * and a parallel sort using MPI, and
 * compares the times
 * 
 */

#include <stdio.h>
#include <stdlib.h>     
#include <string.h>     
#include <time.h>       
#include <mpi.h>


#define  INIT  1        
#define  DATA  2        
#define  ANSW  3        
#define  FINI  4       

// Compariator for qsort()
int compare (const void* left, const void* right);  // for qsort()

// Parallel merge logic under MPI
void parallelMerge (long *vector, int size, int my_height);

// Generate a vector of random data for a size
void getData (long **vPtr, int *sizePtr);

int main ( int argc, char* argv[] )
{
   int my_id, num_procs;
   int rc;                       // Save returns for MPI calls
   int size;                     // Size of the vector being sorted
   long *vector, *solo;          // Copy for sequential sort
   double start, middle, finish; // Variable for times
   int root_process = 0;         // Variable for Root Process

   rc = MPI_Init(&argc, &argv); 
   // Seed for random
   srand(time(NULL));

   // Error Handling
   if (rc < 0)
   {
      puts ("Failed to enroll in MPI.  Abort!");
      exit(-1);
   }

   // Get size from argument, if not prompt in 
   if(argc > 1)
   {
      size = atoi(argv[1]);
   }

   rc = MPI_Comm_rank (MPI_COMM_WORLD, &my_id);
   rc = MPI_Comm_size (MPI_COMM_WORLD, &num_procs);

   // I am the root process!
   if (my_id == root_process)        
   {
      int root_height = 0;
      int node_count = 1;

      // Calculate the Root Height
      while (node_count < num_procs)
      {
         node_count += node_count; root_height++;
      }
      // Print the root height
      printf ("%d processes and root height of %d\n", num_procs, root_height);

      getData (&vector, &size);   // The vector to be sorted.

      // Allocate solo and vector
      solo = (long*) calloc ( size, sizeof *solo );
      memcpy (solo, vector, size * sizeof *solo);

      start = MPI_Wtime();
      // Run MPI Parallel Mergesort
      parallelMerge (vector, size, root_height); 
      middle = MPI_Wtime();
   }
   // I am a node process!
   else                      
   {
      int   iVect[2], height, parent;// Pulled from iVect
      MPI_Status status;          
      // Recieve from node below
      rc = MPI_Recv( iVect, 2, MPI_INT, MPI_ANY_SOURCE, INIT,
           MPI_COMM_WORLD, &status );
      size   = iVect[0];     // Isolate size
      height = iVect[1];     // and height
      // Malloc vector
      vector = (long*) calloc (size, sizeof *vector);

      rc = MPI_Recv( vector, size, MPI_LONG, MPI_ANY_SOURCE, DATA,
           MPI_COMM_WORLD, &status );
      // Recursivly call parallelMerge
      parallelMerge (vector, size, height);

      MPI_Finalize();
      return 0;
   }
   // MPI is finished, so only 1 core now
   // Calculate sequential mergesort for comparison
   qsort( solo, size, sizeof *solo, compare );
   finish = MPI_Wtime();

   printf ("  Parallel:  %3.5f\n", (middle-start));
   printf ("Sequential:  %3.5f\n", (finish-middle));
   printf ("  Speed-up:  %3.5f\n", (finish-middle)/(middle-start));
   // Garuntee cleanup of MPI
   MPI_Finalize();
}


// Shuffle the entire array
void shuffleArray (long* x, int lim)
{  
   while (lim > 1)
   {  
      int item;
      int save = x[lim-1];
      item = (int)((double)rand() * lim / RAND_MAX);
      x[--lim] = x[item];
      x[item] = save;
   } 
}

// Get data for MPI Merge Sort
void getData ( long **vPtr, int *sizePtr )
{
   int size, i;
   long *data;
   // Get size if not command line arg, else print size
   fputs ("Size:  ", stdout);
   if (*sizePtr == 0 )
      scanf ("%d", &size);
   else
   {
      size = *sizePtr;
      printf ("%d\n", size);
   }
   // Malloc Data
   data = (long*) calloc (size, sizeof *data);
   for (i = 0; i < size; i++)
      data[i] = i+1;
   // Randomize Array
   shuffleArray (data, size);
   // Use pass by reference to return data and size
   *vPtr = data;
   *sizePtr = size;
}

// Required by qsort()
int compare ( const void* left, const void* right )
{
   long *lt = (long*) left,
        *rt = (long*) right,
         diff = *lt - *rt;

   if ( diff < 0 ) return -1;
   if ( diff > 0 ) return +1;
   return 0;
}

/**
 * Parallel merge logic under MPI
 *
 * The working core:  each internal node ships its right-hand
 * side to the proper node below it in the processing tree.  It
 * recurses on this function to process the left-hand side, as
 * the node one closer to the leaf level.
 */
void parallelMerge (long *vector, int size, int my_height)
{  
   int parent;
   int my_id, num_procs;
   int rc, nxt, rtChild;

   rc = MPI_Comm_rank (MPI_COMM_WORLD, &my_id);
   rc = MPI_Comm_size (MPI_COMM_WORLD, &num_procs);

   parent = my_id & ~(1<<my_height);
   nxt = my_height - 1;
   if (nxt >= 0)
      rtChild = my_id | (1 << nxt);

   if (my_height > 0)
   {
      // No right child
      if (rtChild >= num_procs)     
         parallelMerge (vector, size, nxt);
      else
      {
         int   left_size  = size / 2,
               right_size = size - left_size;
         long *leftArray  = (long*) calloc (left_size, sizeof *leftArray),
              *rightArray = (long*) calloc (right_size, sizeof *rightArray);
         int   iVect[2];
         int   i, j, k;                // Used in the merge logic
         MPI_Status status;            // Return status from MPI

         memcpy (leftArray, vector, left_size*sizeof *leftArray);
         memcpy (rightArray, vector+left_size, right_size*sizeof *rightArray);

         iVect[0] = right_size;
         iVect[1] = nxt;
         rc = MPI_Send(iVect, 2, MPI_INT, rtChild, INIT, MPI_COMM_WORLD);
         rc = MPI_Send(rightArray, right_size, MPI_LONG, rtChild, DATA, MPI_COMM_WORLD);

         parallelMerge (leftArray, left_size, nxt);

         rc = MPI_Recv(rightArray, right_size, MPI_LONG, rtChild, ANSW, MPI_COMM_WORLD, &status);

         // Merge the two results back into vector
         i = j = k = 0;
         while (i < left_size && j < right_size)
            if (leftArray[i] > rightArray[j])
               vector[k++] = rightArray[j++];
            else
               vector[k++] = leftArray[i++];
         while (i < left_size)
            vector[k++] = leftArray[i++];
         while (j < right_size)
            vector[k++] = rightArray[j++];
      }
   }
   // Sort data in my array
   else
   {
      qsort(vector, size, sizeof *vector, compare);
   }
   // Send data if not parent
   if (parent != my_id)
      rc = MPI_Send(vector, size, MPI_LONG, parent, ANSW, MPI_COMM_WORLD);
}