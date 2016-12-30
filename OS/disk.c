//DISK SCHEDULING
/* Copyright (C) 2016, Lebin Mathew Alex. All rights reserved.*/

#include<stdio.h>

enum Mode {FCFS, SSTF, SCAN} mode;
enum Direction {left, right} dir;

int schedule(int[], int, int[], int, enum Mode);
void swap(int *, int *);
int mod(int);	//mod of a value
void drawGraph(int[], int, int, enum Mode);
int normalize(int[], int, int[]);	//create a sorted list without duplicates

void main()
{
	int i, n, queueSize, index, rp, bound, queue[100];
	
	do
	{
		printf("\nEnter the number of tracks : ");
		scanf("%d", &n);
		
		int list[n]; 
		
		printf("\nEnter the tracks : \n");
		
		for (i=0; i<n; i++)
		{
			scanf("%d", &list[i]);
		}

		int temp[n];
		int x = normalize(list, n, temp);

		for (i=0; i<x; i++)
			printf("%d  ", temp[i]);

		return;
		printf("\nEnter initial head position : ");
		scanf("%d", &queue[0]);
		
		printf("\nEnter Boundary : ");
		scanf("%d", &bound);
		
		printf("\n1 FCFS\n2 SSTF\n3 SCAN\n");
try :	printf("\nEnter Choice : ");
		scanf("%d", &index);

		switch (index)
		{
			case 1 : mode = FCFS; break;
			case 2 : mode = SSTF; break;
			case 3 : mode = SCAN; break;
			default : printf("Invalid Choice!\n"); goto try;
		}
		
		queueSize = schedule(list, n, queue, bound, mode);
		
		printf("\nJobs are scheduled in the order :\n");
		
		for (i=0; i<queueSize; i++)
		{
			printf("%d  ", queue[i]);
		}
			
		printf("\n\n");
		drawGraph(queue, queueSize, bound, mode);
		
		printf("Press 1 to try again!\n");
		scanf("%d", &rp);

	} while (rp == 1);	
}

int schedule(int list[], int n, int queue[], int bound, enum Mode mode)
{
	int i, j, min, queueSize=1; //1 since there's starting track
	
	if (mode == FCFS)
	{
		//just copy the tracks
		for (i=0; i<n; i++)
		{
			if (list[i] != queue[queueSize-1]) //add only if different
			{
				queue[queueSize] = list[i];
				queueSize++;
			}
		}
	}
	else if (mode == SSTF)
	{
		//find the min distance track
		for (i=0; i<n-1; i++)
		{
			min = i+1;
			
			for (j=i+1; j<n; j++)
			{
				if (mod(list[j]-list[i]) < mod(list[min]-list[i]))
				{
					min = j;
				}
			}

			if (list[min] != queue[queueSize-1]) //add only if different
			{
				queue[queueSize] = list[min];
				queueSize++;
			}
		}
	}
	else if (mode == SCAN)
	{
		i = queue[0];
		dir = left;

		while (i <= bound)
		{
			//check if there's any track at current instance
			for (j=0; j<n; j++)
			{
				//add only if different
				if (i == list[j] && list[j] != queue[queueSize-1])
				{
					queue[queueSize] = list[j];
					queueSize++;
				}
			}

			if (i == 0 || i == bound)	//reached left or right end
			{
				if (i != queue[queueSize-1])	//add only if different
				{
					queue[queueSize] = i;
					queueSize++;
				}

				if (i == 0)				//if left end
				{
					dir = right;		//switch direction
					i = queue[0];		//go right from start track
				}
			}

			if (dir == left)
			{
				i--;
			}
			else
			{
				i++;
			}
		}
	}

	return queueSize;
}

void drawGraph(int list[], int n, int bound, enum Mode mode)
{
	int i, j, loc, tempSize, temp[n];
	
	/*
	for (i=0; i<n; i++)	//make a temp list
		temp[i] = list[i];
	
	*/

	tempSize = normalize(list, n, temp);
	
	/*
	for (i=0; i<n; i++)	//sort the list
	{
		for (j=0; j<n-1; j++)
		{
			if (temp[j] > temp[j+1])
				swap(&temp[j], &temp[j+1]);
		}
	}
	*/
	
	/*
	if (mode == SCAN)
	{
		printf("\n\n0\t");
	}
	else
	{
		printf("\n\n0\t%d\t", temp[0]);
	}
	*/
	printf("\n\n");

	if (mode != SCAN && list[0] != 0)	//SCAN has 0 already in it
	{
		printf("0\t");
	}
	
	for (i=0; i<tempSize; i++)		//print rest of the tracks
	{
		if (temp[i] != temp[i-1])
			printf("%d\t", temp[i]);
	}
	
	if (mode != SCAN && list[n-1] != bound)	//SCAN has bound already in it
	{
		printf("%d", bound);
	}
		
	printf("\n\n");
	
	for (i=0; i<n; i++)	//level
	{
		//find location
		for (j=0; j<tempSize; j++)
		{
			if (list[i] == temp[j])
			{
				if (list[i] == 0)
				{
					loc = 0;
				}
				else
				{
					if (mode == SCAN)
						loc = j;
					else
						loc = j+1;		//+1 for left end
					/*
					if (mode == SCAN)
					{
						loc = j;
					}
					else
					{
						if (temp[0] == 0)
							loc = j+1;		//+1 for left end
						else	
							loc = j;		//
					}
					*/
				}
			}
		}
		
		//put loc no of tabs
		for (j=0; j<loc; j++)
		{
			printf("\t");
		}

		printf("x\n\n");
	}
}

int mod(int n)
{
	if (n < 0)
		return -n;
	else
		return n;
}

void swap(int *a, int *b)
{
	int temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}

int normalize(int list[], int n, int temp[])
{
	int i, j, min, tempSize=0;

	for (i=0; i<n; i++)
	{
		min = i;

		for (j=i; j<n; j++)
		{
			if (list[j] < list[min])
			{
				min = j;
			}
		}

		if (tempSize == 0)	//no elements yet
		{
			temp[tempSize] = list[min];
			tempSize++;
		}
		else if (tempSize>0 && temp[tempSize-1] != list[min])	//no duplicates
		{
			temp[tempSize] = list[min];
			tempSize++;
		}
	}

	return tempSize;
}