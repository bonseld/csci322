/**
 * Dylan Bonsell
 * cd.c
 * Solves the producer consumer problem with mutex and condition variables
 * 
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

void *Producer(); 
void *Consumer();


pthread_mutex_t the_mutex;
pthread_cond_t condc, condp;
int buffer = 1;
int numIters;

int main(int argc, char **argv) {
  double begin, end, time_spent;
  begin = clock();
  pthread_t pid, cid; // Initialize Producer and Consumer ID's
  numIters = atoi(argv[1]);

  // Initialize the mutex and condition variables
  pthread_mutex_init(&the_mutex, NULL); 
  pthread_cond_init(&condc, NULL);    
  pthread_cond_init(&condp, NULL);

  // Create the threads
  pthread_create(&cid, NULL, Consumer, NULL);
  pthread_create(&pid, NULL, Producer, NULL);
  pthread_join(cid, NULL);
  pthread_join(pid, NULL);

  // Cleanup Variables
  pthread_mutex_destroy(&the_mutex);  
  pthread_cond_destroy(&condc);   
  pthread_cond_destroy(&condp);  

  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("%f\n", time_spent);

  return 0; 

}

void* Producer() {
  int i;
  for (i = 1; i < numIters; i++) {
    pthread_mutex_lock(&the_mutex);	// Protect buffer
    while (buffer != 0)		       
      pthread_cond_wait(&condp, &the_mutex);
    buffer = i;
    pthread_cond_signal(&condc);	// Wake up Consumer
    pthread_mutex_unlock(&the_mutex);	// Release the buffer
  }
  pthread_exit(0);
}

void* Consumer() {

  int i;
  for (i = 1; i < numIters; i++) {
    pthread_mutex_lock(&the_mutex);	// Protect buffer 
    while (buffer == 0)			
      pthread_cond_wait(&condc, &the_mutex);
    buffer = 0;
    pthread_cond_signal(&condp);	// Wake up Consumer
    pthread_mutex_unlock(&the_mutex);	// Release the buffer
  }
  pthread_exit(0);
}

