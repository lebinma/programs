//Process Fork
//Copyright (c) Lebin Mathew Alex. All rights reserved.

#include<unistd.h>
#include<stdio.h>

void main()
{	
	int pid = fork();
	
	if (!pid)
	{
		printf("Child pid = %d\n", getpid());
		printf("Parent pid = %d\n", getppid());
		printf("Running external application...\n");
		execvp("bin/gnome-mines", "", NULL);
		
	}
	else
	{
		waitpid(pid, 0, 0);
		printf("Finished running.");
	}
} 

