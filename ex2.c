// //Write a function that determines whether a given variable belongs to the stack, heap, or
// //global segments.
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>

// int globalVar = 100;

// const char *find_segment(void *addr)
// {
//     FILE *fp;
//     char line[512];
//     unsigned long start, end;
//     char perms[5];
//     char *p;

//     fp = fopen("/proc/self/maps", "r");

//     while (fgets(line, sizeof(line), fp))
//     {
//         if (sscanf(line, "%lx-%lx %4s", &start, &end, perms) != 3)
//             continue;

//         unsigned long x = (unsigned long)addr;

//         if (x >= start && x < end)
//         {
//             if (strstr(line, "[heap]"))
//                 return "Heap";

//             if (strstr(line, "[stack]"))
//                 return "Stack";

//             /*
//              * Writable mapping belonging to the program:
//              * Global/Data/BSS
//              */
//             if (strchr(perms, 'w'))
//                 return "Global/Data/BSS";

//             return "Other";
//         }
//     }

//     return "Unknown";
// }

// int main()
// {
//     int localVar = 200;
//     int *heapVar = malloc(sizeof(int));

//     *heapVar = 300;

//     printf("Global variable = %p -> %s\n",
//            (void *)&globalVar,
//            find_segment(&globalVar));

//     printf("Heap variable   = %p -> %s\n",
//            (void *)heapVar,
//            find_segment(heapVar));

//     printf("Stack variable  = %p -> %s\n",
//            (void *)&localVar,
//            find_segment(&localVar));

//     free(heapVar);

//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char end;                      /* global segment-এর শেষ সীমা */

void where(void *p, char *name) {
    printf("%-12s %p -> ", name, p);  /* ← শুধু এই লাইনটা নতুন */
    if ((char *)p < &end)
        printf("GLOBAL\n");
    else if ((char *)p < (char *)sbrk(0))
        printf("HEAP\n");
    else
        printf("STACK\n");
}

                          /* global */

int main(void) {
    int g = 10; 
    int local = 5;                    /* stack */
    int *h = malloc(sizeof(int));     /* heap */

    where(&g, "g");
    where(h, "h (malloc)");
    where(&local, "local");

    free(h);
    return 0;
}