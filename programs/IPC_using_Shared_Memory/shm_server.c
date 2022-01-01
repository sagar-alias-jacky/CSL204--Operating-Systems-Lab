#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHMSZ 27

void main()
{
    char c;
    int shmid;
    key_t key;
    char *shm, *s;
    char string[100];

    //Setting a key for the shared memory segment
    key = 5007;

    //Creating the shared memory segment
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0)
    {
        perror("shmget");
        exit(1);
    }

    //Attaching the shared segment to data space
    if ((shm = shmat(shmid, NULL, 0)) == (char *)-1)
    {
        perror("shmat");
        exit(1);
    }

    //Enter the message to shared memory
    s = shm;

    printf("Enter the data to write into the shared memory: ");
    fgets(string, sizeof(string), stdin);
    strcpy(s, string);

    /*Wait until the client process changes the first character of the data in the shared memory to "#", indicating that it has read from the shared memory*/
    while (*shm != '#');
}