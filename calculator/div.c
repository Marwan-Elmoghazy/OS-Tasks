#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if (argc != 3 || argv[1][0] == '\0' || argv[2][0] == '\0')
    {
        fprintf(stderr, "Insufficient number of arguments\n");
        fprintf(stderr, "Usage: %s <num1> <num2>\n", argv[0]);
        return 1;
    }

    // atoi() is a function that converts a string to an integer
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);

    if(num2 == 0) {
        fprintf(stderr, "Cannot perform division by zero\n");
        fprintf(stderr, "Usage: %s <num1> <num2>\n", argv[0]);
        return 1;
    }

    printf("Result: %d\n", num1 / num2);
    printf("Child process finished successfully\n");
    return 0;
}