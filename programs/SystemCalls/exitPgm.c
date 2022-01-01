#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void main()
{
    pid_t pid;
    pid = fork();
    int status;

    if (pid == 0)
    {
        printf("Inside child process!\n");
        sleep(10);
        printf("Child process exited!\n");
        exit(7);
    }
    else
    {
        printf("Inside parent process!\n");
        wait(&status);
        printf("Exit status is: %d\n", WEXITSTATUS(status));
        printf("Parent process exited!");
    }
}