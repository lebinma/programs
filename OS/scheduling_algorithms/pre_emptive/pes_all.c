//PRE-EMPTIVE SCHEDULING
/* Copyright (C) 2016, Lebin Mathew Alex. All rights reserved.*/

#include<unistd.h>
#include<stdio.h>

enum Mode {RROB, SJF, PS} mode;

struct process
{
	//T = time in gantt chart (start time)
	//GT = time in the processed queue (completed time)
	int id, AT, ST, CT, TAT, WT, T, GT; 
	int rem;	//remaining service time
	int priority; //lower means higher
};

void drawChart(struct process[], int);	//draw Gantt Chart
void drawTable(struct process[], int, enum Mode);	//draw Process Table
void sort(struct process[], int);		//sort based on criteria
int process(struct process[], int, struct process[], enum Mode);	//process the processes
int hasRemaining(struct process[], int);

void main()
{
	int n, i, index, rp, mode;	//mode = scheduling mode
	int queueSize;	//queueSize = size of process queue

	do
	{
		printf("\nEnter the number of processes : ");
		scanf("%d", &n);
		struct process p[n], queue[n*n*n];;

		for (i=0; i<n; i++)
		{
			p[i].id = i+1;
			printf("\nEnter AT & ST of P%d : ", i+1);
			scanf("%d%d", &p[i].AT, &p[i].ST);
			p[i].rem = p[i].ST;
		}

		printf("\n1 Round Robin\n2 SJF\n3 Priority Scheduling\n");
try :	printf("\nEnter Choice : ");
		scanf("%d", &index);

		switch (index)
		{
			case 1 : mode = RROB; break;
			case 2 : mode = SJF; break;
			case 3 : mode = PS; break;
			default : printf("Invalid Choice!\n"); goto try;
		}

		if (mode == PS)
		{
			for (i=0; i<n; i++)
			{
				printf("\nEnter Priority of P%d : ", i+1);
				scanf("%d", &p[i].priority);
			}
		}

		sort(p, n);
		queueSize = process(p, n, queue, mode);	//process & get size of queue
		drawTable(p, n, mode);
		drawChart(queue, queueSize);	//chart is independant of mode

		printf("Press 1 to try again!\n");
		scanf("%d", &rp);

	} while (rp == 1);
}

void sort(struct process p[], int n)
{
	int i, j;
	struct process temp;

	for (i=0; i<n-1; i++)	//sort based on AT
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

int process(struct process p[], int n, struct process queue[], enum Mode mode)
{
	int t, j, slice, queueSize=0, i=0;
	struct process *min; //pointer : very important

	t = p[0].AT;

	if (mode == RROB)
	{
		printf("\nEnter the time slice : ");
		scanf("%d", &slice);
		
		for (i=0; i<n; i++)
 		{
 			if (t < p[i].AT) //this process isn't here yet
 			{
 				//if there are ones remaining before this
 				if (hasRemaining(p, i))
 				{
 					i = -1;		 //reset the counter
 					continue;	 //next iteration
 					//i = -1 cuz there's i++
 				}
 				else
 				{
 					t = p[i].AT; //switch to that process
 				}
 			}

 			if (p[i].rem > 0) //has remaining
 			{	
 				p[i].T = t;
			
				//if the remaining ST is > time slice
 				if (p[i].rem >= slice)
 				{
 					t += slice;
 				}
 				else
 				{
 					t += p[i].rem;
 				}
 			
 				//fint WT at the first instance of the process
 				//ie when its ST = remaining time
 				if (p[i].ST == p[i].rem)
 				{
 					p[i].WT = p[i].T - p[i].AT;
 				}
 			
 				p[i].rem -= slice;
 				p[i].GT = t;
 			
 				if (p[i].rem <= 0)	//just finished processing
 				{
 					p[i].CT = t;
 					//now that CT is known, TAT can be calculated
 					p[i].TAT = p[i].CT - p[i].AT;
 				}
 			
 				//push new process to queue
				//if new == top element, then just merge them
				//else, push the new process
				if ((min->id == queue[queueSize-1].id) && queueSize > 0)
				{
					queue[queueSize-1].GT = p[i].GT;
				}
				else
				{
					queue[queueSize] = p[i];
					queueSize++;
				}
 			}

 			//if this is was the last one
 			//and there are remaining processes
 			//reset the counter ASAP
 		
 			if ((i == n-1) && hasRemaining(p, n))
 			{
 				i = -1;
 				//i = -1 cuz there's i++
 			}
 		} 	
	}
	else if (mode == PS || mode == SJF)
	{
		while (hasRemaining(p, n))
		{
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
				if (hasRemaining(p, j) && mode == SJF)
				{
					if ((p[j].rem < min->rem) && p[j].AT <= t)
					{
						if (p[j].rem > 0)
							min = &p[j];
					}
				}
				else if (hasRemaining(p, j) && mode == PS)
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
					
					//skip t if not arrived
					if (min->AT > t)
						t = min->AT;
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
			if ((min->id == queue[queueSize-1].id) && queueSize > 0)
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

void drawTable(struct process p[], int n, enum Mode mode)
{
	int i;

	printf("\n\nAT\tPID\tST\tCT\tTAT\tWT");

	if (mode == PS)
	{
		printf("\tPriority");
	}

	printf("\n-----------------------------------------------------------\n");

	for (i=0; i<n; i++)
	{
		printf("%d\tP%d\t%d\t%d\t%d\t%d", p[i].AT, p[i].id, p[i].ST, p[i].CT, p[i].TAT, p[i].WT);

		if (mode == PS)
		{
			printf("\t%d", p[i].priority);
		}

		printf("\n");
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
