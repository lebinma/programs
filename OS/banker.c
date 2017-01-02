//BANKER'S ALGORITHM
/* Copyright (C) 2016, Lebin Mathew Alex. All rights reserved.*/

#include<stdio.h>
#define true 1
#define false 0
int isSafe(int[], int[][10], int[][10], int, int);  

void main()
{
    int pCount, rCount, i, j, req, pid, request[10];
    int available[10], allocation[10][10], need[10][10], max[10][10];
    
    printf("\nEnter the no of processes : ");
    scanf("%d", &pCount);
    printf("Enter the no of resources : ");
    scanf("%d", &rCount);
    printf("\nEnter the no of instances available : \n");

    for (i=0; i<rCount; i++)
    {
        scanf("%d", &available[i]);
    }

    for (i=0; i<pCount; i++)
    {
        printf("\nEnter the allocation for P%d : \n", i);

        for (j=0; j<rCount; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }
    
    for (i=0; i<pCount; i++)
    {
        printf("\n\nEnter max allocation for P%d : \n", i);

        for (j=0; j<rCount; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }
    
    //calculate need
    for (i=0; i<pCount; i++)
    {
        for (j=0; j<rCount; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    if (isSafe(available, allocation, need, rCount, pCount))
    {
        printf("\n\nSystem is in a safe state.\n");
    }
    else
    {
        printf("\n\nSystem is in an unsafe state.\n");
    }

    printf("\nRequest resources? (1 Yes) : ");
    scanf("%d", &req);

    if (!req)
        return;

    printf("\nEnter PID : ");
    scanf("%d", &pid);

    if (pid >= pCount)
    {
        printf("\nERROR : Invalid PID.\n");
        return;
    }

    printf("\nEnter request : \n");

    for (i=0; i<rCount; i++)
        scanf("%d", &request[i]);

    for (i=0; i<rCount; i++)
    {
        if (request[i] > need[pid][i])
        {
            printf("\nERROR : Maximum exceeded.\n");
            return;
        }

        if (request[i] > available[i])
        {
            printf("\nERROR : Resources not available.\n");
            return;
        }
    }

    //allocate resources
    for (i=0; i<rCount; i++)
    {
        available[i] -= request[i];
        allocation[pid][i] += request[i];
        need[pid][i] -= request[i];
    }

    if (isSafe(available, allocation, need, rCount, pCount))
    {
        printf("\n\nRequest granted. System is in a safe state.\n");
    }
    else
    {
        printf("\n\nRequest declined. System will be in an unsafe state.\n");
    }
}

int isSafe(int available[], int allocation[][10], int need[][10], int rCount, int pCount)
{
    int i, j, k, next, work[10], finish[10];

    for (i=0; i<rCount; i++) 
        work[i] = available[i]; //copy of available vector
    
    for (i=0; i<pCount; i++) 
        finish[i] = false;          //status of processes
    
    //processing starts
    for (i=0; i<pCount; i++)
    {
        int next = -1;           //next process

        for (j=0; j<pCount; j++)
        {
            int isEligible = 1;

            //find process with finish=0 and need<=available
            for (k=0; k<rCount; k++)
            {
                if (need[j][k] > work[k])
                    isEligible = 0;
            }

            if (finish[j] == 0 && isEligible)
            {
                 next = j; 
            }
        }

        if (next == -1)  //no eligible processes left
        {
            break;
        }
        else
        {
            for (j=0; j<rCount; j++)
            {

                work[j] += allocation[next][j];
                finish[next] = true;
            }
        }
    }

    for (i=0; i<pCount; i++)
    {
        if (!finish[i])
            return false;
    }

    return true;
}