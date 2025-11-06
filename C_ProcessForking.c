#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    
    // Create a new process
    pid = fork();
    
    if (pid < 0) {
        // Error handling
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        // This is the CHILD process
        printf("Child process executing.\n");
        printf("Child PID: %d, Parent PID: %d\n", getpid(), getppid());
        exit(0);
    } else {
        // This is the PARENT process
        // Wait for the child to finish
        wait(NULL); 
        printf("Parent process executing.\n");
        printf("Parent PID: %d, Child PID: %d (finished)\n", getpid(), pid);
    }
    
    return 0;
}
