#include <stdio.h>
#include <stdlib.h>

typedef struct block
{
    int blockNo;
    int blockSize;
    int processNo;
    int freeSpace;
    struct block *next;
} block;

block *start = NULL, *end = NULL;

typedef struct process
{
    int status;
    int processNo;
    int processSize;
} process;

process processes[10];

int blocksNum, processNum;

void Display()
{
    int i, flag;
    block *ptr;

    printf("\nProcess No.\tProcess size\tBlock No.\tRemaining space");
    for (i = 0; i < processNum; i++)
    {
        flag = 0;

        printf("\n%d\t\t", processes[i].processNo);
        printf("%d\t\t", processes[i].processSize);
        if (processes[i].status >= 1)
        {
            printf("%d\t\t\t", processes[i].status);
        }
        else
            printf("-\t\t\t");

        for (ptr = start; ptr != NULL; ptr = ptr->next)
        {
            if (ptr->processNo == i + 1)
            {
                printf("%d", ptr->freeSpace);
                flag = 1;
                break;
            }
        }
        if (ptr == NULL && flag == 0)
        {
            printf("-");
        }
    }

    for (i = 0; i < processNum; i++)
    {
        if (processes[i].status < 1)
        {
            printf("\nProcess %d could not be allocated due to inadequate block memory.", processes[i].processNo);
        }
    }

    printf("\n");
}

void FirstFit()
{
    int i, flag = 0;
    block *ptr;

    for (i = 0; i < processNum; i++)
    {
        for (ptr = start; ptr != NULL && flag == 0; ptr = ptr->next)
        {
            if (ptr->processNo == -1 && ptr->blockSize >= processes[i].processSize)
            {
                processes[i].status = ptr->blockNo;
                ptr->processNo = processes[i].processNo;
                ptr->freeSpace = ptr->freeSpace - processes[i].processSize;
                flag = 1;
                break;
            }
        }
        flag = 0;
    }
}

void BestFit()
{
    int i;
    block *smallest, *ptr;

    for (i = 0; i < processNum; i++)
    {
        smallest = NULL;

        for (ptr = start; ptr != NULL; ptr = ptr->next)
        {
            if (ptr->processNo == -1 && ptr->blockSize >= processes[i].processSize)
            {
                if (smallest != NULL)
                {
                    if (ptr->blockSize < smallest->blockSize)
                    {
                        smallest = ptr;
                    }
                }
                else
                    smallest = ptr;
            }
        }

        if (smallest != NULL)
        {
            smallest->processNo = processes[i].processNo;
            smallest->freeSpace = smallest->blockSize - processes[i].processSize;
            processes[i].status = smallest->blockNo;
        }
    }
}

void WorstFit()
{
    int i;
    block *largest, *ptr;

    for (i = 0; i < processNum; i++)
    {
        largest = NULL;

        for (ptr = start; ptr != NULL; ptr = ptr->next)
        {
            if (ptr->processNo == -1 && ptr->blockSize >= processes[i].processSize)
            {
                if (largest != NULL)
                {
                    if (ptr->blockSize > largest->blockSize)
                    {
                        largest = ptr;
                    }
                }
                else
                    largest = ptr;
            }
        }

        if (largest != NULL)
        {
            largest->processNo = processes[i].processNo;
            largest->freeSpace = largest->blockSize - processes[i].processSize;
            processes[i].status = largest->blockNo;
        }
    }
}

void Reset()
{
    int i;
    block *ptr;

    for (i = 0; i < processNum; i++)
    {
        processes[i].status = 0;
    }

    for (ptr = start; ptr != NULL; ptr = ptr->next)
    {
        ptr->processNo = -1;
        ptr->freeSpace = ptr->blockSize;
    }
}

void main()
{
    int i, choice;

    printf("\nEnter the number of blocks: ");
    scanf("%d", &blocksNum);
    for (i = 0; i < blocksNum; i++)
    {
        block *newBlock = (block *)malloc(sizeof(block));
        newBlock->next = NULL;
        newBlock->blockNo = i + 1;
        newBlock->processNo = -1;
        printf("Enter size of block %d: ", i + 1);
        scanf("%d", &newBlock->blockSize);
        newBlock->freeSpace = newBlock->blockSize;

        if (start == NULL && end == NULL)
            start = end = newBlock;
        else
        {
            end->next = newBlock;
            end = newBlock;
        }
    }

    printf("\nEnter the number of processes: ");
    scanf("%d", &processNum);

    for (i = 0; i < processNum; i++)
    {
        processes[i].processNo = i + 1;
        processes[i].status = 0;
        printf("Enter size of process %d: ", i + 1);
        scanf("%d", &processes[i].processSize);
    }

    while (1)
    {
        printf("\nMENU:");
        printf("\n1.First Fit");
        printf("\n2.Best Fit");
        printf("\n3.Worst Fit");
        printf("\n4.Exit");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("\nFirst fit allocation:");
            FirstFit();
            Display();
            break;

        case 2:
            printf("\nBest fit allocation:");
            BestFit();
            Display();
            break;

        case 3:
            printf("\nWorst fit allocation:");
            WorstFit();
            Display();
            break;

        case 4:
            exit(0);

        default:
            printf("\nEnter a valid choice!");
            break;
        }

        Reset();
    }
}
