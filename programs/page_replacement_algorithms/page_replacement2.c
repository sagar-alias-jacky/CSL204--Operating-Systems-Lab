#include <stdio.h>
#include<stdlib.h>

int reference_string[20] = {-1}, frames[5] = {-1};
int no_of_page_references, no_of_frames, page_fault_count;
int i, j, k;

void optimal()
{
    /*Stores the indexes of references of pages that is searched in the 
    reference string during replacement. The page whose index is high implies it is
    not used for the longest period of time*/
    int page_occurence[5];

    /*flag1 and flag2 is set to 1 only when no page fault has occured
    flag3 is set to 1 during page fault and if a particular page is found to be never used
    in future while searching the page for replacement*/
    int flag1, flag2, flag3;

    //Stores the position of the page that is to be replaced
    int pos;

    //Keeps track of the page which is not used for the longest time
    int max;

    page_fault_count = 0;

    printf("\nOptimal page replacement:\n");

    for (i = 0; i < no_of_page_references; i++)
    {
        flag1 = flag2 = 0;

        for (j = 0; j < no_of_frames; j++)
        {
            //No page fault
            if (frames[j] == reference_string[i])
            {
                //flag1 and flag2 is set to 1 as no page fault has occured
                flag1 = flag2 = 1;

                break;
            }
        }

        //Page fault has occured at this point
        if (flag1 == 0)
        {
            for (j = 0; j < no_of_frames; j++)
            {
                //Check existence of free frame
                if (frames[j] == -1)
                {
                    page_fault_count++;
                    frames[j] = reference_string[i];
                    //flag2 is set to 1 as free frame is found
                    flag2 = 1;

                    break;
                }
            }
            //Printing only if page is allocated else page has to be replaced
            if (flag2 == 1)
            {
                for (int a = 0; a < no_of_frames; a++)
                    printf("%d\t", frames[a]);
                printf("Page fault %d\n", page_fault_count);
            }
        }

        //Find page that is not used for the longest period of time
        if (flag2 == 0)
        {
            flag3 = 0;

            for (j = 0; j < no_of_frames; j++)
            {
                /*A value is stored only if a particular page reference 
                has been found in the reference string. Otherwise, its value is
                stored as -1 to indicate that the page is no longer used in future*/
                page_occurence[j] = -1;

                //Searching for page in the reference string
                for (k = i + 1; k < no_of_page_references; k++)
                {
                    if (frames[j] == reference_string[k])
                    {
                        //Add index of page reference if found in the reference string
                        page_occurence[j] = k;

                        break;
                    }
                }
            }

            /*Searching in the array if any reference is not added
            i.e the page is not used in future*/
            for (j = 0; j < no_of_frames; j++)
            {
                /*Check if a page reference is not added
                If true, then the particular page can be replaced*/
                if (page_occurence[j] == -1)
                {
                    pos = j;
                    /*flag3 set to 1 as a page who will not be used in future is already found
                    (No need to find the page which is not used for the longest time)*/
                    flag3 = 1;

                    break;
                }
            }

            /*All pages in the frames are present in the reference string
            Find the page which is not used for the longest time*/
            if (flag3 == 0)
            {
                max = page_occurence[0];
                pos = 0;

                for (j = 1; j < no_of_frames; j++)
                {
                    /*If the current page's index is greater, i.e not used for a longer time
                    ('index' corresponds to the position in the reference string)*/
                    if (page_occurence[j] > max)
                    {
                        max = page_occurence[j];
                        pos = j;
                    }
                }
            }

            frames[pos] = reference_string[i];
            page_fault_count++;

            for (int a = 0; a < no_of_frames; a++)
                printf("%d\t", frames[a]);
            printf("Page fault %d\n", page_fault_count);
        }
    }

    printf("Total no. of page faults: %d\n", page_fault_count);
}

void lru()
{
   
    int page_occurence[5];

    int flag1, flag2, flag3;

    int pos;

    int min;

    page_fault_count = 0;

    printf("\nLRU page replacement:\n"); 

    for (i = 0; i < no_of_page_references; i++)
    {
        flag1 = flag2 = 0;

        for (j = 0; j < no_of_frames; j++)
        {
          
            if (frames[j] == reference_string[i])
            {
                flag1 = flag2 = 1;

                break;
            }
        }

        if (flag1 == 0)
        {
            for (j = 0; j < no_of_frames; j++)
            {
               
                if (frames[j] == -1)
                {
                    page_fault_count++;
                    frames[j] = reference_string[i];
                    flag2 = 1;

                    break;
                }
            }
        
            if (flag2 == 1)
            {
                for (int a = 0; a < no_of_frames; a++)
                    printf("%d\t", frames[a]);
                printf("Page fault %d\n", page_fault_count);
            }
        }

        if (flag2 == 0)
        {
            for (j = 0; j < no_of_frames; j++)
            {

                page_occurence[j] = -1;

                for (k = i - 1; k >= 0; k--)
                {
                    if (frames[j] == reference_string[k])
                    {
                        
                        page_occurence[j] = k;

                        break;
                    }
                }
            }

            min = page_occurence[0];
            pos = 0;

            for (j = 1; j < no_of_frames; j++)
            {
     
                if (page_occurence[j] < min)
                {
                    min = page_occurence[j];
                    pos = j;
                }
            }

            frames[pos] = reference_string[i];
            page_fault_count++;

            for (int a = 0; a < no_of_frames; a++)
                printf("%d\t", frames[a]);
            printf("Page fault %d\n", page_fault_count);
        }
    }

    printf("Total no. of page faults: %d\n", page_fault_count);
}

void fifo()
{
    //Initialize page fault count to 0
    page_fault_count = 0;

    //Stores the current index of the frame array
    int index = 0;

    /*'available' is set to 1 if a particular page  
    is found in one of the frames*/
    int available;

    printf("\nFIFO page replacement:\n");

    for (i = 0; i < no_of_page_references; i++)
    {
        available = 0;

        for (j = 0; j < no_of_frames; j++)
        {
            //Check if page is already allocated to a frame (no page fault)
            if (frames[j] == reference_string[i])
                available = 1;
        }

        //The page is not occupied in the frame (condition of page fault)
        if (available == 0)
        {
            //Assign page reference to frame and increment the frame index
            frames[index] = reference_string[i];
            index = (index + 1) % no_of_frames;

            page_fault_count++;

            for (j = 0; j < no_of_frames; j++)
                printf("%d\t", frames[j]);
            printf("Page fault %d\n", page_fault_count);
        }
    }

    printf("Total no. of page faults: %d\n", page_fault_count);
}

void main()
{
    int ch;

    printf("Enter no. of page references: ");
    scanf("%d", &no_of_page_references);

    printf("Enter reference string: ");
    for (i = 0; i < no_of_page_references; i++)
        scanf("%d", &reference_string[i]);

    printf("Enter no. of frames: ");
    scanf("%d", &no_of_frames);

    while (1)
    {
        printf("\nMenu:\n1. FIFO\n2. LRU\n3. Optimal\n4. Exit\nEnter choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            fifo();

            // for (int i = 0; i < no_of_frames; i++)
                // frames[i] = -1;

            break;

        case 2:
            lru();

            // for (int i = 0; i < no_of_frames; i++)
                // frames[i] = -1;

            break;

        case 3:
            optimal();
            // for (int i = 0; i < no_of_frames; i++)
                // frames[i] = -1;
            break;
        case 4:
            exit(0);
        default:
            printf("\nPlease enter a valid choice");
        }
        
        for (int i = 0; i < no_of_frames; i++)
            frames[i] = -1;
    }
}