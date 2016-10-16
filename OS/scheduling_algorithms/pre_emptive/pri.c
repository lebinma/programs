//PRIORITY SCHEDULING (PRE-EMPTIVE)
/* Copyright (C) 2016, Lebin Mathew Alex. All rights reserved.*/

#include<unistd.h>
#include<stdio.h>

struct process
{
	//T = time in gantt table
	//GT = time in the processed queue
	int id, AT, ST, CT, TAT, WT, T, GT; 
	int rem;	//remaining service time
	int priority; //lower means higher
};

void drawChart(struct process[], int);	//draw Gantt Chart
void drawTable(struct process[], int);	//draw Process Table
void sort(struct process[], int);		//sort based on criteria
int process(struct process[], int, struct process[]);	//process the processes
int hasRemaining(struct process[], int);


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

void test(char c, int n)
{
	printf("TEST %c = %d\n", c, n);
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

int process(struct process p[], int n, struct process queue[])
{
	int i, t, j, queueSize=0;
	struct process *min; //pointer : very important 

	t = p[0].AT;

	while (hasRemaining(p, n))
	{

	}


	/*
		while has remaining, increments t by 1. after incrementing
		check if there are any processes that have arrived. If yes, then find the highest priority
		one among them. 
	*/


 	for (i=0; i<n; i++)
 	{
 		/*
 		debugDrawTable(p, n);
 		safeBreakLevel--;
 		if(safeBreakLevel == 0)
 		{
 			printf("\nSAFE BREAK COMPLETE.");
 			break;
 		}
 		*/
 		
 		if (t < p[i].AT) //this process isn't here yet
 		{
 			t = p[i].AT; //switch to that process
 		}
 		
 		//find arrived process with higher priority than this
 		min = &p[i];
 		
 		for (j=0; j<n; j++)
 		{
 			if ((p[j].AT <= p[i].AT) && (p[j].priority < p[i].priority))
 			{
 				min = &p[j];
 			}
 		}
 		
 		min->T = t;
 		
 		//execute the process till higher priority arrives
 		while (min->rem > 0)
 		{ 		 			
 			//fint WT at the first instance of the process
 			//ie when its ST = remaining time
 			if (min->ST == min->rem)
 			{
 				min->WT = min->T - min->AT;
 			}
 		
 			t++;
 			min->rem--;
 			
 			//higher priority arrived 
 			for (j=0; j<n; j++)
 			{
 				if ((p[j].AT <= t) && min->priority > p[j].priority)
 				{
 					//push current process to queue before switching
 					min->GT = t;
 					queue[queueSize] = *min;	//push to queue
 					queueSize++;
 					min = &p[j];
 				}
 			}
 		}
 		
 		//push this process after processing (rem = 0)
 		min->GT = t;
 		queue[queueSize] = *min;	//push to queue
 		queueSize++;
 		p[i].CT = t;
 		
 		//now that CT is known, TAT can be calculated
 		p[i].TAT = p[i].CT - p[i].AT;	
 	}	
 	
 	return queueSize;
}

void drawTable(struct process p[], int n)
{
	int i;
	
	printf("\n\nAT\tPID\tST\tCT\tTAT\tWT\n");
	printf("------------------------------------------------\n");
	
	for (i=0; i<n; i++)
	{
		printf("%d\tP%d\t%d\t%d\t%d\t%d\n", p[i].AT, p[i].id, p[i].ST, p[i].CT, p[i].TAT, p[i].WT);
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
		if (p[i].T < p[i-1].GT)	
		{
			printf("|%d|   P%d   |%d|", p[i].T, p[i].id, p[i].GT);
		}
		else if (p[i].T == p[i-1].GT)	//if equal, no duplication
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

