//PRIORITY SCHEDULING (PRE-EMPTIVE)
/* Copyright (C) 2016, Lebin Mathew Alex. All rights reserved.*/

#include<unistd.h>
#include<stdio.h>

struct process
{
	//T = time in gantt chart (start time)
	//GT = time in the processed queue (completed time)
	int id, AT, ST, CT, TAT, WT, T, GT; 
	int rem;	//remaining service time
	int priority; //lower means higher
};

void drawChart(struct process[], int);	//draw Gantt Chart
void drawTable(struct process[], int);	//draw Process Table
void sort(struct process[], int);		//sort based on criteria
int process(struct process[], int, struct process[]);	//process the processes
int hasRemaining(struct process[], int);
struct process* getMin(struct process[], int, int); //get next process
struct process* getSkippable(struct process [], int, int);



//-------------DEBUGGING FUNCTIONS---------------------------

int safeBreakLevel = 6;	//infinite loop breaking mechanism

void debugDrawQueue(struct process p[], int n)
{
	int i;
	printf("\n\n----DEBUG DRAW QUEUE----\n");
	
	for (i=0; i<n; i++)
	{
		printf("p%d  ", p[i].id);
	}	
	
	printf("\n-------------------------------\n\n");
}

void test(char c[], int n)
{
	printf("TEST %s = %d\n", c, n);
}

void debugDrawTable(struct process p[], int n)
{
	int i;
	printf("\n\n----DEBUG DRAW TABLE----");
	
	printf("\n\nAT\tPID\tST\tREM\n");
	printf("------------------------------------------------\n");
	
	for (i=0; i<n; i++)
	{
		printf("%d\tP%d\t%d\t%d\n", p[i].AT, p[i].id, p[i].ST, p[i].rem);
	}
	
	printf("\n-------------------------------\n\n");
}

//-----------------------------------------------------------




void main()
{
	int n, i, queueSize;	//queueSize = size of process queue

	printf("Enter the number of processes : ");
	scanf("%d", &n);
	struct process p[n], temp, queue[n*n*n];
	
	for (i=0; i<n; i++)
	{
		p[i].id = i+1;
		printf("\nEnter AT, ST & Priority of P%d : ", i+1);
		scanf("%d%d%d", &p[i].AT, &p[i].ST, &p[i].priority);
		p[i].rem = p[i].ST;
	}
	
	sort(p, n);
	queueSize = process(p, n, queue);	//process & get size of queue
	drawTable(p, n);
	drawChart(queue, queueSize);
}

void sort(struct process p[], int n)
{
	int i, j;
	struct process temp;
	
	for (i=0; i<n-1; i++)			//sort based on AT
	{
		for (j=0; j<n-1; j++)
		{
			if (p[j].AT > p[j+1].AT)
			{
				temp = p[j];
				p[j] = p[j+1];
				p[j+1] = temp;
			}
		}
	}
}

int process(struct process p[], int n, struct process queue[])
{
	int t, j, queueSize=0, i=0;
	struct process *min;//pointer : very important
	
	t = p[0].AT;
	
	while (hasRemaining(p, n))
	{	
		//debugDrawTable(p,n);

 		if (t < p[i].AT) //this process isn't here yet
 		{
 			//if there are ones remaining before this
 			if (hasRemaining(p, i))
 			{
 				i = 0;		 //reset the counter
 				continue;	 //next iteration
 			}
 			else
 			{
 				t = p[i].AT; //switch to that process
 			}
 		}
		
		//find the minimum process at the current instance
		
		min = &p[0];
		
		for (j=0; j<n; j++)
		{
			if (hasRemaining(p, j))
			{
				if ((p[j].priority < min->priority) && p[j].AT <= t)
				{
					if (p[j].rem > 0)
						min = &p[j];
				}
			}
			else
			{
				min = &p[j];
			}
		}
		
		//fint WT at the first instance of the process
 		//ie when its ST = remaining time
 		if (min->ST == min->rem)
 		{
 			min->WT = t - min->AT;
 		}
		
		//process the minimum node
		min->T = t;
		t++;
		min->rem--;
		min->GT = t;
		
		//if just done processing, find it's CT & TAT
		if (min->rem == 0)
		{
			min->CT = t;
			min->TAT = min->CT - min->AT;
		}
			
 		//push new process to queue
		//if new == top element, then just merge them
		//else, push the new process
		if (min->id == queue[queueSize-1].id)
		{
			queue[queueSize-1].GT = min->GT;
		}
		else
		{
			queue[queueSize] = *min;
			queueSize++;
		}
			
 		//if this is was the last one
 		//and there are remaining processes
 		//reset the counter ASAP
 		
 		if ((i == n-1) && hasRemaining(p, n))
 		{

 			i = -1;
 		}
 		
 		i++;
	}
	
	return queueSize;
}

int hasRemaining(struct process p[], int limit)
{
	int i;
	
	for (i=0; i<limit; i++)
	{
		if (p[i].rem > 0)
			return 1;
	}
	
	return 0;
}

void drawTable(struct process p[], int n)
{
	int i;

	printf("\n\nAT\tPID\tPri\tST\tCT\tTAT\tWT\n");
	printf("---------------------------------------------------\n");
	
	for (i=0; i<n; i++)
	{
		printf("%d\tP%d\t%d\t%d\t%d\t%d\t%d\n", p[i].AT, p[i].id,p[i].priority, p[i].ST, p[i].CT, p[i].TAT, p[i].WT);
	}
	
}

void drawChart(struct process p[], int n)
{
	int i=1;
	
	printf("\n\n");
	
	if (p[0].T == 0)						//first process
	{
		printf("|0|   P%d   |%d|", p[0].id, p[0].GT);
	}
	else
	{
		printf("|0|------|%d|   P%d   |%d|", p[0].T, p[0].id, p[0].GT);
	}
	
	for (i=1; i<n; i++)
	{
		if (p[i].T == p[i-1].GT)	//if equal, no duplication
		{
			
			printf("   P%d   |%d|", p[i].id, p[i].GT);
		}
		else							//lag
		{
			printf("------|%d|   P%d   |%d|", p[i].T, p[i].id, p[i].GT);
		}
	}
	
	printf("\n\n");
}
