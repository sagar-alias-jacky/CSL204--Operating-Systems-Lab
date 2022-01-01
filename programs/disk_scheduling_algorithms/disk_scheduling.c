#include <stdio.h>
#include <stdlib.h>

int req[20], temp[20];
int num, n, current;

void reset()
{
    n = num;
    for (int i = 0; i < n; i++)
        req[i] = temp[i];
}
//Finds location of current
int find_loc_of_current()
{
    for (int i = 0; i < n; i++)
    {
        if (req[i] == current)
            return i;
    }
}

void sort()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (req[i] > req[j])
            {
                int temp = req[i];
                req[i] = req[j];
                req[j] = temp;
            }
        }
    }
}

void cscan()
{
    int seek_count = 0, head, current_track;
    int loc_of_current;
    int choice;
    int last;
    printf("Enter last track of disk: ");
    scanf("%d", &last);
    //Adding 0, current and last track of disk to request set
    req[n] = 0;
    n++;
    req[n] = current;
    n++;
    req[n] = last;
    n++;
    sort();
    loc_of_current = find_loc_of_current();
    printf("Choose direction - 1. Forward, 2. Backward: ");
    scanf("%d", &choice);
    printf("Seek sequence: ");
    if (choice == 1)
    {
        for (int i = loc_of_current, head = current; i < n; i++)
        {
            printf("%d -> ", req[i]);
            current_track = req[i];
            seek_count += abs(current_track - head);
            head = current_track;
        }
        for (int i = 0, head = req[n - 1]; i < loc_of_current; i++)
        {
            if (i != loc_of_current - 1)
                printf("%d -> ", req[i]);
            else
                printf("%d", req[i]);
            current_track = req[i];
            seek_count += abs(current_track - head);
            head = current_track;
        }
    }
    else
    {
        for (int i = loc_of_current, head = current; i >= 0; i--)
        {
            printf("%d -> ", req[i]);
            current_track = req[i];
            seek_count += abs(current_track - head);
            head = current_track;
        }
        for (int i = n - 1, head = req[0]; i > loc_of_current; i--)
        {
            if (i != loc_of_current + 1)
                printf("%d -> ", req[i]);
            else
                printf("%d", req[i]);
            current_track = req[i];
            seek_count += abs(current_track - head);
            head = current_track;
        }
    }
    printf("\nTotal cylinder movements: %d\n", seek_count);
}

void scan()
{
    int seek_count = 0, head, current_track;
    int loc_of_current;
    int choice;
    int last;
    //Adding current to request set
    req[n] = current;
    n++;
    printf("Choose direction - 1. Forward, 2. Backward: ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("Enter last track of disk: ");
        scanf("%d", &last);
        //Adding last track of disk to request set
        req[n] = last;
        n++;
        sort();
        loc_of_current = find_loc_of_current();
        printf("Seek sequence: ");
        for (int i = loc_of_current, head = current; i < n; i++)
        {
            printf("%d -> ", req[i]);
            current_track = req[i];
            seek_count += abs(current_track - head);
            head = current_track;
        }
        for (int i = loc_of_current - 1, head = req[n - 1]; i >= 0; i--)
        {
            if (i != 0)
                printf("%d -> ", req[i]);
            else
                printf("%d", req[i]);
            current_track = req[i];
            seek_count += abs(current_track - head);
            head = current_track;
        }
    }
    else
    {
        req[n] = 0;
        n++;
        sort();
        loc_of_current = find_loc_of_current();
        printf("Seek sequence: ");
        for (int i = loc_of_current, head = current; i >= 0; i--)
        {
            printf("%d -> ", req[i]);
            current_track = req[i];
            seek_count += abs(current_track - head);
            head = current_track;
        }
        for (int i = loc_of_current + 1, head = req[0]; i < n; i++)
        {
            if (i != n - 1)
                printf("%d -> ", req[i]);
            else
                printf("%d", req[i]);
            current_track = req[i];
            seek_count += abs(current_track - head);
            head = current_track;
        }
    }
    printf("\nTotal cylinder movements: %d\n", seek_count);
}

void fcfs()
{
    int seek_count = 0;
    int current_track;
    int head = current;
    printf("Seek sequence: ");
    for (int i = 0; i < n; i++)
    {
        if (i != n - 1)
            printf("%d -> ", req[i]);
        else
            printf("%d", req[i]);
        current_track = req[i];
        seek_count += abs(current_track - head);
        head = current_track;
    }
    printf("\nTotal cylinder movements: %d\n", seek_count);
}

void main()
{
    int ch;
    printf("Enter no. of requests: ");
    scanf("%d", &n);
    num = n;
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &req[i]);
        temp[i] = req[i];
    }
    printf("Enter current head position: ");
    scanf("%d", &current);
    do
    {
        printf("\n1. FCFS\t\t2. SCAN\n3. C-SCAN\t4. Exit\nEnter choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("\nFCFS:\n");
            fcfs();
            break;
        case 2:
            printf("\nSCAN:\n");
            scan();
            break;
        case 3:
            printf("\nC-SCAN:\n");
            cscan();
            break;
        }
        reset();
    } while (ch >= 1 && ch <= 3);
}
