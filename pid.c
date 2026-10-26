#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char globBuf[65536];
int primes[] = {2, 3, 5, 7};

static int square(int x)
{
    int result;
    result = x * x;
    return result;
}

static void doCalc(int val)
{
    printf("The square of %d is %d\n", val, square(val));

    if (val < 1000)
    {
        int t;
        t = val * val * val;
        printf("The cube of %d is %d\n", val, t);
    }
}

int main()
{
    static int key = 9973;
    static char mbuf[10240000];

    char *p;
    p = malloc(1024);

    printf("main       = %p\n", (void *)main);
    printf("doCalc     = %p\n", (void *)doCalc);
    printf("globBuf    = %p\n", (void *)globBuf);
    printf("primes     = %p\n", (void *)primes);
    printf("key        = %p\n", (void *)&key);
    printf("mbuf       = %p\n", (void *)mbuf);
    printf("heap       = %p\n", (void *)p);
    printf("stack      = %p\n", (void *)&p);

    printf("PID = %d\n", getpid());

    getchar();

    free(p);
    return 0;
}