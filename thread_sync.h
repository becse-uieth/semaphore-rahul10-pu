#include <unistd.h>
#include <sys/types.h> 
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>

void handler ( void *ptr );
pthread_barrier_t barrier;

int worker = 2; // number of workers
int job = 4; // number of jobs for each worker

int main()
{

    int i = 0;
    pthread_t thread_a;

    pthread_barrier_init(&barrier, NULL, worker);

    for (i; i < worker; i++)
    {  
       int *n_workers = malloc(sizeof(*n_workers));  
       *n_workers = i;                   
       pthread_create (&thread_a, NULL, (void *) &handler, n_workers);
    }

    pthread_join(thread_a, NULL);

    pthread_barrier_destroy(&barrier);

    pthread_exit(0);
}

void handler ( void *ptr )
{
    int x = *((int *) ptr);
    int i = 0;

    for (i; i < job; i++)
    {
       printf("Worker %d: Doing Job %d\n", x, i);  
       pthread_barrier_wait(&barrier);
    }
}
