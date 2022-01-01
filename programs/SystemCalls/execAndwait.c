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
        printf("You are inside the child process with pid %d, which is now going to invoke the exec() system call to replace the contents of this program with that of program 2.\n",
               getpid());
        execlp("./program2", "program2", NULL);
    }
    else
    {
        wait(NULL);
        printf("The child process with pid %d has terminated.\n", pid);
        printf("Now we are inside the parent process with pid %d.\n", getpid());
    }
}
