#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
    int fd;
    pid_t pid;
    char buffer[100];

    fd = open("data.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);

    pid = fork();

    if (pid == 0)
    {
        write(fd, "Hello from Child\n", 17);
        printf("Child wrote data\n");
        exit(0);
    }
    else
    {
        wait(NULL);

        lseek(fd, 0, SEEK_SET);
        read(fd, buffer, 99);
        buffer[99] = '\0';

        printf("Parent read: %s", buffer);

        exit(0);
    }
}