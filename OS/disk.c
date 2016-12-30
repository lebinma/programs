//DISK SCHEDULING
//Alpha Version

#include<stdio.h>

enum Mode {FCFS, SSTF, SCAN} mode;
enum Direction {left, right} dir;

int schedule(int[], int, int, enum Mode);
void swap(int *, int *);
int mod(int);	//mod of a value
void drawGraph(int[], int, int, enum Mode);

void main()
{
	int i, n, index, rp, seek, bound;
	
	do
	{
		printf("\nEnter the number of tracks : ");
		scanf("%d", &n);
		
		int list[n+2]; //+2 is for boundaries in SCAN
		
		printf("\nEnter the tracks : \n");
		
		for (i=1; i<=n; i++)
		{
			scanf("%d", &list[i]);
		}
		
		printf("\nEnter initial head position : ");
		scanf("%d", &list[0]);
		
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
		
		seek = schedule(list, n, bound, mode);
		
		printf("\nJobs are scheduled in the order :\n");
		
		for (i=0; i<=n; i++)
		{
			printf("%d  ", list[i]);
		}
		
		if (mode == SCAN)
			printf("%d  %d", list[n+1], list[n+2]);
			
		printf("\n\n");
		
		drawGraph(list, n, bound, mode);
			
		printf("\n\nSeek time = %d\n\n", seek);
		
		printf("Press 1 to try again!\n");
		scanf("%d", &rp);

	} while (rp == 1);	
}

int schedule(int list[], int n, int bound, enum Mode mode)
{
	int i, j, k, min, temp[n], size=1, seek=0;
	
	temp[0] = list[0];
	
	if (mode == FCFS)
	{
	}
	else if (mode == SSTF)
	{
		for (i=0; i<n; i++)
		{
			min = i+1;
			
			for (j=i+1; j<=n; j++)
			{
				if (mod(list[j]-list[i]) < mod(list[min]-list[i]))
				{
					min = j;
				}
			}
			
			swap(&list[i+1], &list[min]);
		}
	}
	else if (mode == SCAN)
	{
		i = list[0];
		dir = left;
		n += 2;		//+2 locations for boundaries
		
		while (i <= bound)
		{
			for (k=1; k<=n; k++)
			{
				if (i == list[k])
				{
					temp[size] = i;
					size++;
				}
			}
			
			if (i == 0)
			{
				temp[size] = i;
				size++;
				dir = right;
				i = list[0];	
			}
			else if (i == bound)
			{
				temp[size] = bound;
				size++;
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
		
		for (i=1; i<=n; i++)
		{
			list[i] = temp[i];
		}
	}
	
	for (i=0; i<n; i++)
	{
		seek += mod(list[i+1]-list[i]);
	}

	return seek;
}

void drawGraph(int list[], int n, int bound, enum Mode mode)
{
	int i, j, loc, temp[n];
	
	if (mode == SCAN)
		n += 2;			//+2 locations for boundaries
	
	for (i=0; i<=n; i++)	//make a temp list
		temp[i] = list[i];
	
	for (i=0; i<=n; i++)	//sort the list
	{
		for (j=0; j<n; j++)
		{
			if (temp[j] > temp[j+1])
				swap(&temp[j], &temp[j+1]);
		}
	}
	
	if (mode == SCAN)
	{
		printf("\n\n0\t");
	}
	else
	{
		printf("\n\n0\t%d\t", temp[0]);
	}
	
	for (i=1; i<=n; i++)
	{
		if (temp[i] != temp[i-1])
			printf("%d\t", temp[i]);
	}
	
	if (mode != SCAN)
		printf("%d", bound);
		
	printf("\n\n");
	
	for (i=0; i<=n; i++)	//level
	{
		//find location
		for (j=0; j<=n; j++)
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
						loc = j+1;
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



