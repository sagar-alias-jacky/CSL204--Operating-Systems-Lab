#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void main()
{
    int fd = open("file.txt", O_CREAT);
    printf("File opened with file descriptor value fd: %d\n", fd);

    if (close(fd) < 0)
    {
        printf("An error occurred while closing the file.\n");
    }
    else
        printf("File closed successfully!\n");
}
