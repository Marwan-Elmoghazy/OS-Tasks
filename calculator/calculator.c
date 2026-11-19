#include <stdio.h> // for the printf() function
#include <stdlib.h> // for the exit() function
//#include <stdbool.h> // for the bool type
#include <string.h> // for the string manipulation functions
#include <unistd.h> // for the fork() and exec() functions
#include <sys/wait.h> // for the waitpid() and WEXITSTATUS() functions

    // for printing prompt and reading a line and split it into command (add , ...) + up to 2 arguments (the 2 numbers we do the operations on)
    void read_command(char *command, char *arg1, char *arg2) {
        char line[100];

        printf("calculator > ");
        fflush(stdout);

        // Clear old values from the previous loop repeating
        // the '\0' is the null terminator (ASCII value 0) which is a hidden "stop sign" that marks the end of every string in C lang
        command[0] = '\0';
        arg1[0] = '\0';
        arg2[0] = '\0';

        // fgets() is a function that reads a line from a specified place (from user input here) and stores it in a string (line here) and returns a pointer to the string (line here) or NULL if an error occurs or end of file is reached
        char *input = fgets(line, sizeof(line), stdin);
        if (input != NULL) {
            // 0 -> 6 = 7 (including the \0) & 0 -> 63 = 64 (including the \0)
            sscanf(line, "%6s %63s %63s", command, arg1, arg2);
        }
    }

    // swapping the child process with the matching operation program 
    void run_child(char *command, char *arg1, char *arg2) {
        char *args[] = {command , arg1, arg2, NULL};
        char *negate_args[] = {command , arg1, NULL};

        // strcmp() is a function that compares two string and returns 0 if they are equal and a non-zero value if they are not equal
        if (strcmp(command, "add") == 0) {

            execv("./.compiled/add", args);

        } else if (strcmp(command, "sub") == 0) {

            execv("./.compiled/sub", args);

        } else if (strcmp(command, "mul") == 0) {

            execv("./.compiled/mul", args);

        } else if (strcmp(command, "div") == 0) {

            execv("./.compiled/div", args);

        } else if (strcmp(command, "negate") == 0) {

            execv("./.compiled/negate", negate_args);

        } else {

            // if the command is not recognized, print an error message and exit with a non-zero status
            fprintf(stderr, "Unknown inputed command: %s\nAvailable commands: add, sub, mul, div, negate", command);
            exit(1);

        }

        perror("execv failed");
        exit(21);
    }

    // creating the child process by forking and using run_child() function and waiting for it to finish
    void execute_command(char *command, char *arg1, char *arg2) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork failed");
            exit(1);
        }

        if (pid == 0) {
            run_child(command, arg1, arg2);
        }

        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Exit status: %d\n", WEXITSTATUS(status));
        } else {
            printf("Exit status: 1\n");
        }
    }

    int main(void) {
        char command[7];
        char arg1[64];
        char arg2[64];
        // a trigger to keep the calculator running until the user types "exit"
        int keep_running = 1;

        // using a do-while loop to keep the calculator running until the user types "exit"
        do {
            read_command(command, arg1, arg2);

            if (strcmp(command, "exit") == 0) {

                keep_running = 0;
                printf("Calculator terminated.\n");

            } else if (command[0] != '\0') {

                execute_command(command, arg1, arg2);

            }
            
        } while (keep_running);

        return 0;
    }
