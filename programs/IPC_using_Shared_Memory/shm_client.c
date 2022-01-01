#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHMSZ 27

void main()
{
    int shmid;
    key_t key;
    char *shm, *s;

    //Get the shared segment named "5007" created by the server
    key = 5007;

    //Locate the segment
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0)
    {
        perror("shmget");
        exit(1);
    }

    //Attach segment to data space
    if ((shm = shmat(shmid, NULL, 0)) == (char *)-1)
    {
        perror("shmat");
        exit(1);
    }

    //Read from the shared memory
    printf("Data read from the shared memory: ");
    for (s = shm; *s != '\0'; s++)
    {
        putchar(*s);
    }

    /*Change the first character of the data stored in the shared memory to "#" indicating that we have read from the shared memory*/
    *shm = '#';
}