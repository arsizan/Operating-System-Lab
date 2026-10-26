#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int a, b;
    int pipefd[2];
    pid_t pid;
    int result;

    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);

    // Addition
    pipe(pipefd);

    pid = fork();

    if (pid == 0)
    {
        close(pipefd[0]);

        result = a + b;

        write(pipefd[1], &result, sizeof(result));

        close(pipefd[1]);
        exit(0);
    }
    else
    {
        close(pipefd[1]);

        wait(NULL);

        read(pipefd[0], &result, sizeof(result));

        printf("Addition       = %d\n", result);

        close(pipefd[0]);
    }

    // Subtraction
    pipe(pipefd);

    pid = fork();

    if (pid == 0)
    {
        close(pipefd[0]);

        result = a - b;

        write(pipefd[1], &result, sizeof(result));

        close(pipefd[1]);
        exit(0);
    }
    else
    {
        close(pipefd[1]);

        wait(NULL);

        read(pipefd[0], &result, sizeof(result));

        printf("Subtraction    = %d\n", result);

        close(pipefd[0]);
    }

    // Multiplication
    pipe(pipefd);

    pid = fork();

    if (pid == 0)
    {
        close(pipefd[0]);

        result = a * b;

        write(pipefd[1], &result, sizeof(result));

        close(pipefd[1]);
        exit(0);
    }
    else
    {
        close(pipefd[1]);

        wait(NULL);

        read(pipefd[0], &result, sizeof(result));

        printf("Multiplication  = %d\n", result);

        close(pipefd[0]);
    }

    // Division
    pipe(pipefd);

    pid = fork();

    if (pid == 0)
    {
        close(pipefd[0]);

        result = a / b;

        write(pipefd[1], &result, sizeof(result));

        close(pipefd[1]);
        exit(0);
    }
    else
    {
        close(pipefd[1]);

        wait(NULL);

        read(pipefd[0], &result, sizeof(result));

        printf("Division       = %d\n", result);

        close(pipefd[0]);
    }

    return 0;
}