#include <stdio.h>
#include <stdlib.h>

#include <string.h> // for the string manipulation functions
#include <unistd.h> // for the fork() and exec() functions
#include <wait.h> // for the waitpid() function
//#include <sys/wait.h>

int main(){
    int x = 0;
    pid_t pid = fork();
    
    if (pid == 0) {
        x = 5 + 10;
        printf("in child process\n");
        exit(x);
    }else if (pid > 0){
        int status;
        waitpid(pid , &status, 0);
        if(WIFEXITED(status)){
            printf("in parent process and x = %d\n", WEXITSTATUS(status));
        }
    }


}
