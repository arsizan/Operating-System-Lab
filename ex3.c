#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <string> <num1> <num2>\n", argv[0]);
        return 1;
    }
    char *s = argv[1];
    int len = strlen(s);

    /* (a) উল্টো */
    printf("Reverse: ");
    for (int i = len - 1; i >= 0; i--)
        printf("%c", s[i]);
    printf("\n");

    /* (b) vowel ও consonant */
    int v = 0, c = 0;
    for (int i = 0; i < len; i++) {
        char ch = s[i];
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' ||
            ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U')
            v++;
        else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
            c++;
    }
    printf("Vowels: %d, Consonants: %d\n", v, c);

    /* (c) যোগ ও গুণ */
    int a = atoi(argv[2]);
    int b = atoi(argv[3]);
    printf("Sum: %d\n", a + b);
    printf("Product: %d\n", a * b);
    return 0;
}