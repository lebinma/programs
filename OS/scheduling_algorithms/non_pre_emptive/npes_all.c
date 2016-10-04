//NON PRE-EMPTIVE SCHEDULING
/* Copyright (C) 2016, Lebin Mathew Alex. All rights reserved.*/

#include<unistd.h>
#include<stdio.h>

enum Mode {FCFS, SJF, PS} mode;

struct process
{
	int id, AT, ST, CT, TAT, WT, T; //T = time in gantt table
	int status; //0 not processed, 1 waiting, 2 processed
	int priority; //lower means higher
};

void drawChart(struct process[], int);	//draw Gantt Chart
void drawTable(struct process[], int, enum Mode);	//draw Process Table
void sort(struct process[], int);		//sort based on criteria
void process(struct process[], int, enum Mode);	//process the processes
void swap(struct process *, struct process *);	//swap processes

void main()
{
	int n, i, index, rp, mode;	//mode = scheduling mode

	do
	{
		printf("\nEnter the number of processes : ");
		scanf("%d", &n);
		struct process p[n];

		for (i=0; i<n; i++)
		{
			p[i].id = i+1;
			printf("\nEnter AT & ST of P%d : ", i+1);
			scanf("%d%d", &p[i].AT, &p[i].ST);
			p[i].status = 0;
		}

		printf("\n1 FCFS\n2 SJF\n3 Priority Scheduling\n");
try :	printf("\nEnter Choice : ");
		scanf("%d", &index);

		switch (index)
		{
			case 1 : mode = FCFS; break;
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
		process(p, n, mode);
		drawTable(p, n, mode);
		drawChart(p, n);	//chart is independant of mode

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

void process(struct process p[], int n, enum Mode mode)
{
	int i, j, t;
	struct process *min; //pointer : very important

	t = p[0].AT;

	for (i=0; i<n; i++)
	{
		if (mode == FCFS)
		{
			for (i=0; i<n; i++)	//find CT
			{
			//if there's lag, set timer to next process

			if (t < p[i].AT)
				t = p[i].AT;

			p[i].CT = t + p[i].ST;
			p[i].T = p[i].CT-p[i].ST;
			t = p[i].CT;
			}
		}
		else if (mode == SJF || mode == PS)
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

					if (mode == SJF && p[j].ST < min->ST)	//find min ST node
					{
						min = &p[j];
					}
					else if (mode == PS && p[j].priority < min->priority)	//find min ST node
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
