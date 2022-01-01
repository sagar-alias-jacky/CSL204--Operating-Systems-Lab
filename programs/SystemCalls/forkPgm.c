#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void main()
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        printf("Fork unsuccessful!\n");
    }
    else if (pid == 0)
    {
        printf("We are inside the child process with process ID: %d\n", getpid());
        printf("The return value of fork() system call in the child process: %d\n", pid);
    }
    else
    {
        printf("We are inside the parent process with process ID: %d\n", getpid());
        printf("The return value of fork() system call in the parent process: %d\n", pid);
    }
}