#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        printf("Child process\n");
        printf("Child PID = %d\n", getpid());

        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("Parent is waiting for child...\n");

        wait(&status);

        printf("Parent process continues\n");
        printf("Child has terminated\n");

        exit(EXIT_SUCCESS);
    }

    return 0;
}