#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <semaphore.h>

int main()
{
    int *counter;
    sem_t *lock;

    counter = mmap(NULL,
                   sizeof(int),
                   PROT_READ | PROT_WRITE,
                   MAP_SHARED | MAP_ANONYMOUS,
                   -1,
                   0);

    lock = mmap(NULL,
                sizeof(sem_t),
                PROT_READ | PROT_WRITE,
                MAP_SHARED | MAP_ANONYMOUS,
                -1,
                0);

    *counter = 0;

    // Process-shared semaphore
    sem_init(lock, 1, 1);

    int numChildren = 4;
    int iterations = 10000;

    for (int i = 0; i < numChildren; i++)
    {
        if (fork() == 0)
        {
            for (int j = 0; j < iterations; j++)
            {
                sem_wait(lock);

                (*counter)++;

                sem_post(lock);
            }

            exit(0);
        }
    }

    for (int i = 0; i < numChildren; i++)
        wait(NULL);

    printf("Expected counter = %d\n",
           numChildren * iterations);

    printf("Actual counter   = %d\n", *counter);

    sem_destroy(lock);

    munmap(counter, sizeof(int));
    munmap(lock, sizeof(sem_t));

    return 0;
}