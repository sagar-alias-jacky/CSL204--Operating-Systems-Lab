#include <stdio.h>
#include <stdlib.h>

int i, j, k, sequence_index, flag;
int no_of_processes, no_of_instances;
int available[5], safe_sequence[10], finish[10] = {0};
int allocation[10][5], max[10][5], need[10][5];

/*finish array is initialized to 0 to signify none of the processes are allocated recsources.
If a process is allocated resources, the corresponding finish index is set to 1*/

void entry()
{
    printf("Enter no. of processes: ");
    scanf("%d", &no_of_processes);

    printf("Enter no. of resource instances: ");
    scanf("%d", &no_of_instances);

    printf("\nEnter the max matrix:\n");
    for (i = 0; i < no_of_processes; i++)
        for (j = 0; j < no_of_instances; j++)
            scanf("%d", &max[i][j]);

    printf("\nEnter the allocation matrix:\n");
    for (i = 0; i < no_of_processes; i++)
        for (j = 0; j < no_of_instances; j++)
            scanf("%d", &allocation[i][j]);

    printf("\nEnter the available resources: ");
    for (i = 0; i < no_of_instances; i++)
        scanf("%d", &available[i]);
}

void display()
{
    printf("\nProcess\t\tMax\t\tAllocation\tAvailable\n");
    for (i = 0; i < no_of_processes; i++)
    {
        printf("P%d\t\t", i);

        for (j = 0; j < no_of_instances; j++)
            printf("%d  ", max[i][j]);

        printf("\t");

        for (j = 0; j < no_of_instances; j++)
            printf("%d  ", allocation[i][j]);

        if (i == 0)
        {
            printf("\t");

            for (j = 0; j < no_of_instances; j++)
                printf("%d  ", available[j]);
        }

        printf("\n");
    }
}

void bankers_algorithm()
{
    /*Assigning index variable of safe sequence to beginning of the safe sequence array*/
    sequence_index = 0;

    /*Calculating need of each process*/
    for (i = 0; i < no_of_processes; i++)
        for (j = 0; j < no_of_instances; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    for (k = 0; k < no_of_processes; k++)
    {
        for (i = 0; i < no_of_processes; i++)
        {
            if (finish[i] == 0)
            {
                /*flag is set to 1 if any of the resource instance need of a process 
                is greater than the available instances*/
                flag = 0;

                for (j = 0; j < no_of_instances; j++)
                {
                    if (need[i][j] > available[j])
                    {
                        flag = 1;
                        break;
                    }
                }

                /*Need of the process is less than the available instances*/
                if (flag == 0)
                {
                    safe_sequence[sequence_index++] = i;

                    for (j = 0; j < no_of_instances; j++)
                        available[j] += allocation[i][j];

                    finish[i] = 1;
                }
            }
        }
    }
}

void main()
{
    entry();

    display();

    bankers_algorithm();

    for (i = 0; i < no_of_processes; i++)
    {
        if (finish[i] != 1)
        {
            printf("\nSafe state is not achieved.\n");
            exit(0);
        }
    }

    printf("\nSafe state is achieved.");
    printf("\nSafe sequence: ");
    for (i = 0; i < no_of_processes - 1; i++)
        printf("P%d -> ", safe_sequence[i]);
    printf("P%d\n", safe_sequence[no_of_processes - 1]);
}