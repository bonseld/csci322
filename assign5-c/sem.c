 /**
 * Dylan Bonsell
 * sem.c
 * Solves the producer consumer problem with mutex and condition variables 
 * 
 */

#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>

#define SHARED 1

void *Producer(); 
void *Consumer();

sem_t empty, full;    /* the global semaphores */
int buffer;             /* shared buffer         */
int numIters;

int main(int argc, char *argv[]) {
  double begin, end, time_spent;
  begin = clock();
  pthread_t pid, cid;   // Initialize Producer and Consumer ID's
  numIters = atoi(argv[1]);

  // Initialize the semaphore
  sem_init(&empty, SHARED, 1);  /* sem empty = 1 */
  sem_init(&full, SHARED, 0);   /* sem full = 0  */

  // Create the threads
  pthread_create(&pid, NULL, Producer, NULL);
  pthread_create(&cid, NULL, Consumer, NULL);
  pthread_join(pid, NULL);
  pthread_join(cid, NULL);

  // Cleanup Variables
  sem_destroy(&empty);
  sem_destroy(&full);

  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("%f\n", time_spent);

  return 0;
}

void *Producer() {
  int i;
  for (i = 0; i < numIters; i++) {
    sem_wait(&empty);
    buffer = i;
    sem_post(&full);
  }
  pthread_exit(0);
}

void *Consumer() {
  int total = 0, i;
  for (i = 0; i < numIters; i++) {
    sem_wait(&full);
    total = total + buffer;
    sem_post(&empty);
  }
  pthread_exit(0);
}