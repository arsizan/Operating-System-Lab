//Write a program that prints its process ID and parent process ID. Extend it to periodically
//print the parent process ID. What happens if you terminate the parent process?
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid == 0)
    {
        // Child
        for (int i = 0; i < 6; i++)
        {
            printf("Child: PID = %d, PPID = %d\n", getpid(), getppid());
            sleep(2);
        }

        exit(EXIT_SUCCESS);
    }
    else
    {
        // Parent
        printf("Parent: PID = %d\n", getpid());

        sleep(5);

        printf("Parent is terminating...\n");
        exit(EXIT_SUCCESS);
    }

    return 0;
}