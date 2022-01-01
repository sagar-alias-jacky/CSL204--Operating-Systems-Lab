#include <stdio.h>
#include <unistd.h>

void main()
{
    printf("Hello this is program 2.\n");
    printf("The pid of the child process %d remains the same even though its contents have been replaced by program 2.\n", getpid());
}
