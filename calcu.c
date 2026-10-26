#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    double a, b;
    char op[4] = {'+', '-', '*', '/'};

    setbuf(stdout, NULL);                    /* output buffer বন্ধ */

    printf("Enter two numbers: ");
    scanf("%lf %lf", &a, &b);
    printf("Parent PID: %d\n\n", getpid());

    for (int i = 0; i < 4; i++) {
        pid_t pid = fork();

        if (pid < 0) {                       /* ERROR */
            perror("fork");
            exit(1);
        }
        else if (pid == 0) {                 /* CHILD: একটা operation */
            double r = 0;
            if (op[i] == '+')      r = a + b;
            else if (op[i] == '-') r = a - b;
            else if (op[i] == '*') r = a * b;
            else if (b != 0)       r = a / b;
            else {
                printf("Child %d: cannot divide by zero\n", getpid());
                exit(1);
            }
            printf("Child %d (parent %d): %g %c %g = %g\n",
                   getpid(), getppid(), a, op[i], b, r);
            exit(0);
        }
        else {                               /* PARENT: অপেক্ষা */
            wait(NULL);
        }
    }

    printf("\nParent: all calculations done.\n");
    return 0;
}