#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    char msg[] = "Hel";
    char buf[100];

    pipe(fd);                                 /* fd[0] = read, fd[1] = write */

    if (fork() == 0) {                        /* CHILD: পড়বে */
        close(fd[1]);
        read(fd[0], buf, sizeof(buf));
        printf("Child received: %s\n", buf);
        close(fd[0]);
    } else {                                  /* PARENT: লিখবে */
        close(fd[0]);
        write(fd[1], msg, strlen(msg) + 1);   /* +1 = '\0'-ও পাঠাও */
        close(fd[1]);
        wait(NULL);
    }
    return 0;
}