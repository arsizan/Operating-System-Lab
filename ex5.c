#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>

int main()
{
    int *counter;

    counter = mmap(NULL,
                   sizeof(int),
                   PROT_READ | PROT_WRITE,
                   MAP_SHARED | MAP_ANONYMOUS,
                   -1,
                   0);

    *counter = 0;

    int numChildren = 4;
    int iterations = 10000;

    for (int i = 0; i < numChildren; i++)
    {
        if (fork() == 0)
        {
            for (int j = 0; j < iterations; j++)
            {
                int temp = *counter;

                // Delay to increase chance of race
                usleep(1);

                *counter = temp + 1;
            }

            exit(0);
        }
    }

    // Parent waits for all children
    for (int i = 0; i < numChildren; i++)
        wait(NULL);

    printf("Expected counter = %d\n",
           numChildren * iterations);

    printf("Actual counter   = %d\n", *counter);

    munmap(counter, sizeof(int));

    return 0;
}