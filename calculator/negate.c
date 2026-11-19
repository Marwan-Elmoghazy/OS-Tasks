#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if (argc != 2 || argv[1][0] == '\0')
    {
        fprintf(stderr, "Insufficient number of arguments\n");
        fprintf(stderr, "Usage: %s <num1>\n", argv[0]);
        return 1;
    }

    // atoi() is a function that converts a string to an integer
    int num = atoi(argv[1]);

    printf("Result: %d\n", -num);
    printf("Child process finished successfully\n");
    return 0;
}