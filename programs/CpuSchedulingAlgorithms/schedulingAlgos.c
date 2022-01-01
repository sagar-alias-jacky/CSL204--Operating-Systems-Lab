#include <stdio.h>

typedef struct process
{
    int id;
    int arrival_time;
    int completion_time;
    int burst_time;
    int turnaround_time;
    int waiting_time;
    int remaining_time;
    int priority;
    int position_in_queue;
} process;

int i, j, no_of_processes, time_quantum;
float av_turnaround_time, av_waiting_time;
process processes[10], temp;

void Input()
{
    printf("Enter no. of processes: ");
    scanf("%d", &no_of_processes);

    for (i = 0; i < no_of_processes; i++)
    {
        processes[i].id = i + 1;

        printf("Enter arrival time of process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);

        printf("Enter burst time of process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);

        printf("Enter priority of process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
    }
}

void display()
{
    printf("\nProcess ID\tArrival time\tBurst time\tTurnaround time\t\tWaiting time\n");

    for (i = 0; i < no_of_processes; i++)
        printf("%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, processes[i].turnaround_time, processes[i].waiting_time);

    printf("Average Turnaround time: %.2f", av_turnaround_time);
    printf("\nAverage Waiting time: %.2f\n", av_waiting_time);
}

void reset()
{
    for (i = 0; i < no_of_processes; i++)
    {
        processes[i].completion_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].position_in_queue = 0;
    }
}

void swap(int i, int j)
{
    temp = processes[i];
    processes[i] = processes[j];
    processes[j] = temp;
}

void sort_by_arrival_time()
{
    for (i = 0; i < no_of_processes; i++)
    {
        for (j = i + 1; j < no_of_processes; j++)
        {
            if (processes[i].arrival_time > processes[j].arrival_time)
                swap(i, j);

            else if (processes[i].arrival_time == processes[j].arrival_time)
            {
                if (processes[i].burst_time > processes[j].burst_time)
                    swap(i, j);
                else if (processes[i].burst_time == processes[j].burst_time)
                {
                    if (processes[i].id > processes[j].id)
                        swap(i, j);
                }
            }
        }
    }
}

void sort_by_arrival_time_fcfs()
{
    for (i = 0; i < no_of_processes; i++)
    {
        for (j = i + 1; j < no_of_processes; j++)
        {
            if (processes[i].arrival_time > processes[j].arrival_time)
                swap(i, j);

            else if (processes[i].arrival_time == processes[j].arrival_time)
            {
                if (processes[i].id > processes[j].id)
                    swap(i, j);
            }
        }
    }
}

void sort_by_process_id()
{
    for (i = 0; i < no_of_processes; i++)
    {
        for (j = i + 1; j < no_of_processes; j++)
        {
            if (processes[i].id > processes[j].id)
                swap(i, j);
        }
    }
}

void sort_by_burst_time()
{
    for (i = 0; i < no_of_processes; i++)
    {
        for (j = i + 1; j < no_of_processes; j++)
        {
            if (processes[i].burst_time > processes[j].burst_time)
                swap(i, j);

            if (processes[i].burst_time == processes[j].burst_time)
            {
                if (processes[i].id > processes[j].id)
                    swap(i, j);
            }
        }
    }
}

void sort_by_priority()
{
    for (i = 0; i < no_of_processes; i++)
    {
        for (j = i + 1; j < no_of_processes; j++)
        {
            if (processes[i].priority > processes[j].priority)
                swap(i, j);

            if (processes[i].priority == processes[j].priority)
            {
                if (processes[i].id > processes[j].id)
                    swap(i, j);
            }
        }
    }
}

void fcfs()
{
    av_turnaround_time = av_waiting_time = 0.0;

    sort_by_arrival_time_fcfs();

    processes[0].completion_time = processes[0].arrival_time + processes[0].burst_time;
    processes[0].turnaround_time = processes[0].completion_time - processes[0].arrival_time;
    processes[0].waiting_time = processes[0].turnaround_time - processes[0].burst_time;

    av_turnaround_time += processes[0].turnaround_time;
    av_waiting_time += processes[0].waiting_time;

    for (i = 1; i < no_of_processes; i++)
    {
        if (processes[i].arrival_time <= processes[i - 1].completion_time)
            processes[i].completion_time = processes[i - 1].completion_time + processes[i].burst_time;
        else
            processes[i].completion_time = processes[i].arrival_time + processes[i].burst_time;

        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

        av_turnaround_time += processes[i].turnaround_time;
        av_waiting_time += processes[i].waiting_time;
    }

    av_turnaround_time /= no_of_processes;
    av_waiting_time /= no_of_processes;

    sort_by_process_id();

    display();
}

void sjf()
{
    int previous_completion_time, smallest_burst_time, loc_of_shortest;
    int found_with_early_AT, flag = 0;
    av_turnaround_time = av_waiting_time = 0.0;

    for (i = 0; i < no_of_processes; i++)
    {
        if (processes[i].arrival_time > 0)
            flag = 1;
    }

    if (flag == 1)
        sort_by_arrival_time();
    else
        sort_by_burst_time();

    processes[0].completion_time = processes[0].arrival_time + processes[0].burst_time;
    processes[0].turnaround_time = processes[0].completion_time - processes[0].arrival_time;
    processes[0].waiting_time = processes[0].turnaround_time - processes[0].burst_time;

    av_turnaround_time += processes[0].turnaround_time;
    av_waiting_time += processes[0].waiting_time;

    for (i = 1; i < no_of_processes; i++)
    {
        previous_completion_time = processes[i - 1].completion_time;
        smallest_burst_time = 100;
        found_with_early_AT = 0;

        for (j = i; j < no_of_processes; j++)
        {
            if (processes[j].arrival_time <= previous_completion_time && processes[j].burst_time < smallest_burst_time)
            {
                found_with_early_AT = 1;
                loc_of_shortest = j;
                smallest_burst_time = processes[j].burst_time;
            }

            if (found_with_early_AT == 0)
            {
                if (processes[j].arrival_time >= previous_completion_time && processes[j].burst_time < smallest_burst_time)
                {
                    loc_of_shortest = j;
                    smallest_burst_time = processes[j].burst_time;
                }
            }
        }

        if (found_with_early_AT == 1)
            processes[loc_of_shortest].completion_time = previous_completion_time + processes[loc_of_shortest].burst_time;
        else
            processes[loc_of_shortest].completion_time = processes[loc_of_shortest].arrival_time + processes[loc_of_shortest].burst_time;

        processes[loc_of_shortest].turnaround_time = processes[loc_of_shortest].completion_time - processes[loc_of_shortest].arrival_time;
        processes[loc_of_shortest].waiting_time = processes[loc_of_shortest].turnaround_time - processes[loc_of_shortest].burst_time;

        swap(loc_of_shortest, i);

        av_turnaround_time += processes[i].turnaround_time;
        av_waiting_time += processes[i].waiting_time;
    }

    av_turnaround_time /= no_of_processes;
    av_waiting_time /= no_of_processes;

    sort_by_process_id();

    display();
}

int finished_execution()
{
    for (i = 0; i < no_of_processes; i++)
    {
        if (processes[i].remaining_time != 0)
            return 0;
    }

    return 1;
}

void round_robin()
{
    int smallest_position, count = 0, first_in_queue, clock = 0, position = 1;
    av_turnaround_time = av_waiting_time = 0.0;

    printf("\nEnter time quantum: ");
    scanf("%d", &time_quantum);

    for (i = 0; i < no_of_processes; i++)
        processes[i].remaining_time = processes[i].burst_time;

    sort_by_arrival_time_fcfs();

    while (finished_execution() == 0)
    {
        for (i = 0; i < no_of_processes; i++)
        {
            if (processes[i].arrival_time == clock)
                processes[i].position_in_queue = position++;
        }

        if (count == time_quantum)
        {
            count = 0;
            processes[first_in_queue].position_in_queue = position++;
        }

        for (i = 0, smallest_position = 100; i < no_of_processes; i++)
        {
            if (processes[i].position_in_queue < smallest_position && processes[i].position_in_queue != 0 && processes[i].remaining_time != 0)
            {
                first_in_queue = i;
                smallest_position = processes[i].position_in_queue;
            }
        }

        clock++;
        processes[first_in_queue].remaining_time--;
        count++;

        if (processes[first_in_queue].remaining_time == 0)
        {
            count = 0;

            processes[first_in_queue].position_in_queue = 0;
            processes[first_in_queue].completion_time = clock;
            processes[first_in_queue].turnaround_time = processes[first_in_queue].completion_time - processes[first_in_queue].arrival_time;
            processes[first_in_queue].waiting_time = processes[first_in_queue].turnaround_time - processes[first_in_queue].burst_time;

            av_turnaround_time += processes[first_in_queue].turnaround_time;
            av_waiting_time += processes[first_in_queue].waiting_time;
        }
    }

    av_turnaround_time /= no_of_processes;
    av_waiting_time /= no_of_processes;

    sort_by_process_id();

    display();
}

void priority()
{
    int previous_completion_time, highest_priority, loc_of_highest;
    int found_with_early_AT, flag = 0;
    av_turnaround_time = av_waiting_time = 0.0;

    for (i = 0; i < no_of_processes; i++)
    {
        if (processes[i].arrival_time > 0)
            flag = 1;
    }

    if (flag == 1)
        sort_by_arrival_time();
    else
        sort_by_priority();

    processes[0].completion_time = processes[0].arrival_time + processes[0].burst_time;
    processes[0].turnaround_time = processes[0].completion_time - processes[0].arrival_time;
    processes[0].waiting_time = processes[0].turnaround_time - processes[0].burst_time;

    av_turnaround_time += processes[0].turnaround_time;
    av_waiting_time += processes[0].waiting_time;

    for (i = 1; i < no_of_processes; i++)
    {
        previous_completion_time = processes[i - 1].completion_time;
        highest_priority = 20;
        found_with_early_AT = 0;

        for (j = i; j < no_of_processes; j++)
        {
            if (processes[j].arrival_time <= previous_completion_time && processes[j].priority < highest_priority)
            {
                found_with_early_AT = 1;
                loc_of_highest = j;
                highest_priority = processes[j].priority;
            }

            if (found_with_early_AT == 0)
            {
                if (processes[j].arrival_time >= previous_completion_time && processes[j].priority < highest_priority)
                {
                    loc_of_highest = j;
                    highest_priority = processes[j].priority;
                }
            }
        }

        if (found_with_early_AT == 1)
            processes[loc_of_highest].completion_time = previous_completion_time + processes[loc_of_highest].burst_time;
        else
            processes[loc_of_highest].completion_time = processes[loc_of_highest].arrival_time + processes[loc_of_highest].burst_time;

        processes[loc_of_highest].turnaround_time = processes[loc_of_highest].completion_time - processes[loc_of_highest].arrival_time;
        processes[loc_of_highest].waiting_time = processes[loc_of_highest].turnaround_time - processes[loc_of_highest].burst_time;

        swap(loc_of_highest, i);

        av_turnaround_time += processes[i].turnaround_time;
        av_waiting_time += processes[i].waiting_time;
    }

    av_turnaround_time /= no_of_processes;
    av_waiting_time /= no_of_processes;

    sort_by_process_id();

    display();
}

void main()
{
    int choice;

    Input();

    do
    {
        printf("\n1. FCFS\n2. SJF\n3. Priority\n4. Round Robin\n5. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            fcfs();
            break;

        case 2:
            sjf();
            break;

        case 3:
            priority();
            break;

        case 4:
            round_robin();
            break;

        default:
            printf("\nPlease enter a valid choice!\n");
        }

        reset();
    } while (choice >= 1 && choice <= 4);
}