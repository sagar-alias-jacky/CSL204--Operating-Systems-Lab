#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

void main()
{
    struct stat buf;
    stat("forkPgm.c", &buf);
    printf("File size: %ld bytes\n", buf.st_size);
}