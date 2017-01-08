//PAGE REPLACEMENT ALGORITHMS
/* Copyright (C) 2016, Lebin Mathew Alex. All rights reserved.*/

#include<stdio.h>

struct page
{
	int id, lastSeen, freq;
};

enum Mode {FIFO, LRU, LFU};
void schedule(struct page[], struct page[], int, int, enum Mode);
int isHit(struct page, struct page[], int);	//returns location if hit
int getFreeFrame(struct page[], int);		//returns location of a free frame

void main()
{
	int pCount, fCount, i, index, rp;

	do
	{
		printf("\nEnter no of pages : ");
		scanf("%d", &pCount);
		printf("Enter no of frames : ");
		scanf("%d", &fCount);
		printf("\nEnter the page sequence :\n");

		struct page p[pCount], f[fCount];

		for (i=0; i<pCount; i++)
		{
			scanf("%d", &p[i].id);
			p[i].lastSeen = 0;
			p[i].freq = 0;
		}
		
		for (i=0; i<fCount; i++)
			f[i].id = -1;

		printf("\n1 FIFO\n2 LRU\n3 LFU\n");
try :	printf("\nEnter Choice : ");
		scanf("%d", &index);

		switch (index)
		{
			case 1 : schedule(p, f, pCount, fCount, FIFO) ; break;
			case 2 : schedule(p, f, pCount, fCount, LRU); break;
			case 3 : schedule(p, f, pCount, fCount, LFU); break;
			default : printf("Invalid Choice!\n"); goto try;
		}

		printf("\n\nPress 1 to try again!\n");
		scanf("%d", &rp);

	} while (rp == 1);
}

void schedule(struct page p[], struct page f[], int pCount, int fCount, enum Mode mode)
{
	int i, fault, next, k, hit, j=0;

	//Table headers
	printf("\n\nPage\tMemory\t\tFault\n--------------------------------\n");

	for (i=0; i<pCount; i++)
	{
		fault = 0;
		hit = isHit(p[i], f, fCount);

		if (hit >= 0)		//page hit
		{
			f[hit].lastSeen = i;	//for LRU
			f[hit].freq++;			//for LFU
		}
		else				//page fault
		{
			fault = 1;

			if (mode == FIFO)
			{
				f[j] = p[i];		//replace page
				j = (j+1) % fCount;		
			}
			else if (mode == LRU || mode == LFU)
			{
				next = getFreeFrame(f, fCount);

				if (next == -1)	//no free frames available
				{
					next = 0;	//start with first frame

					for (j=0; j<fCount; j++)
					{
						if (mode == LRU && f[j].lastSeen < f[next].lastSeen)
						{
							next = j;
						}

						if (mode == LFU && f[j].freq < f[next].freq)
						{
							next = j;
						}
					}
				}

				f[next] = p[i];
				f[next].lastSeen = i;	//for LRU
				f[next].freq++;			//for LFU
			}
		}

		printf("%d\t", p[i].id);

		for (k=0; k<fCount; k++)
		{
			if (f[k].id == -1)
			{
				printf("-  ");
				continue;
			}

			printf("%d  ", f[k].id);
		}

		printf("\t");

		if (fault)
			printf("*");

		printf("\n");
	}
}

int isHit(struct page p, struct page f[], int fCount)
{
	int i;

	for (i=0; i<fCount; i++)
	{
		if (p.id == f[i].id)
			return i;			//page hit
	}

	return -1;					//page fault
}

int getFreeFrame(struct page f[], int fCount)
{
	int i;

	for (i=0; i<fCount; i++)
	{
		if (f[i].id == -1)
			return i;
	}

	return -1;		//no free frames available
}