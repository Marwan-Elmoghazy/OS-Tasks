#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    char *args[] = {"expr", "2", "+", "3", NULL};

    //fflush(stdout);
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }
    if (pid == 0) {
        execvp("expr", args);
        perror("expr");
        exit(127);
    }

    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        printf("child process exited successfully (PID %d) status = %d\n", pid, WEXITSTATUS(status));
    } else {
        printf("child process failed status = %d\n", WEXITSTATUS(status));
    }
    return 0;
}