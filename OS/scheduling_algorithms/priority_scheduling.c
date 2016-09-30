//PRIORITY SCHEDULING
//Copyright (c) Lebin Mathew Alex. All rights reserved.

#include<unistd.h>
#include<stdio.h>

struct process
{
	int id, AT, ST, CT, TAT, WT, T; //T = time in gantt table
	int status; //0 not processed, 1 waiting, 2 processed
	int priority; //lower means higher
};

void drawChart(struct process[], int);	//draw Gantt Chart
void drawTable(struct process[], int);	//draw Process Table
void sort(struct process[], int);		//sort based on criteria
void process(struct process[], int);	//process the processes
void swap(struct process *, struct process *);	//swap processes

void main()
{
	int n, i;

	printf("Enter the number of processes : ");
	scanf("%d", &n);
	struct process p[n];
	
	for (i=0; i<n; i++)
	{
		p[i].id = i+1;
		printf("\nEnter AT, ST & Priority of P%d : ", i+1);
		scanf("%d%d%d", &p[i].AT, &p[i].ST, &p[i].priority);
		p[i].status = 0;
	}
	
	sort(p, n);
	process(p, n);
	drawTable(p, n);
	drawChart(p, n);
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

void process(struct process p[], int n)
{
	int i, j, t;
	struct process *min; //pointer : very important 

	t = p[0].AT;

	for (i=0; i<n; i++)
	{
		//if there's lag, set timer to next process
		
		if (t < p[i].AT)
			t = p[i].AT; 
		
		//initialise min process (which has arrived)
			
		for (j=i; j<n; j++)
		{
			if ((p[j].AT <= t) && (p[j].status >= 0)) //status = 0 or 1
			{
				min = &p[j];
				break;
			}
		}
			
		//find arrived unexecuted processes & the min of them
			
		for (j=i; j<n; j++)
		{
			if ((p[j].AT <= t) && (p[j].status >= 0))
			{
				p[j].status = 1;		//waiting
					
				if (p[j].priority < min->priority)	//find min ST node
				{
					min = &p[j];
				}
			}
		}
			
		min->status = 2;
		min->T = t;
		min->CT = t + min->ST;
		t = min->CT;
			
		if (min->id != p[i].id)		//swap only if different
			swap(&p[i], min);
	}

	for (i=0; i<n; i++)	//find TAT and WT
	{
		p[i].TAT = p[i].CT-p[i].AT;
		
		if (p[i-1].CT > p[i].AT)
			p[i].WT = p[i-1].CT-p[i].AT;
		else
			p[i].WT = 0;
	}
	
	p[0].WT=0;
}

void drawTable(struct process p[], int n)
{
	int i;
	
	printf("\n\nAT\tPID\tST\tCT\tTAT\tWT\tPriority\n");
	printf("-----------------------------------------------------------\n");
	
	for (i=0; i<n; i++)
	{
		printf("%d\tP%d\t%d\t%d\t%d\t%d\t%d\n", p[i].AT, p[i].id, p[i].ST, p[i].CT, p[i].TAT, p[i].WT, p[i].priority);
	}
}

void drawChart(struct process p[], int n)
{
	int i=1;
	
	printf("\n\n");
	
	if (p[0].T == 0)						//first process
	{
		printf("|0|   P%d   |%d|", p[0].id, p[0].CT);
	}
	else
	{
		printf("|0|------|%d|   P%d   |%d|", p[0].T, p[0].id, p[0].CT);
	}
	
	for (i=1; i<n; i++)
	{
		if (p[i].T < p[i-1].CT)	
		{
			printf("|%d|   P%d   |%d|", p[i].T, p[i].id, p[i].CT);
		}
		else if (p[i].T == p[i-1].CT)	//if equal, no duplication
		{
			
			printf("   P%d   |%d|", p[i].id, p[i].CT);
		}
		else							//lag
		{
			printf("------|%d|   P%d   |%d|", p[i].T, p[i].id, p[i].CT);
		}
	}
	
	printf("\n\n");
}

void swap(struct process *p, struct process *q)
{
	struct process temp;
	
	temp = *p;
	*p = *q;
	*q = temp;
}

