//Process Chain
//Copyright (c) Lebin Mathew Alex. All rights reserved.

#include<unistd.h>
#include<stdio.h>

void main()
{	
	int pid, i;	//no of childs
	
	for (i=0; i<4; i++)
	{
		pid = fork();
		
		if (!pid)  //child
		{
			printf("Level %d\n--------------------\nParent id =  %d\nChild id = %d\n\n\n", i+1, getppid(), getpid());
		}
		else
		{
			wait();
			break;
		}
	}
} 

