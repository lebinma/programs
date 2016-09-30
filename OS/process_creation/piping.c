//Two Way Piping
//Copyright (c) Lebin Mathew Alex. All rights reserved.

#include<stdio.h>
#include<unistd.h>

void main()
{
	int c2p[2], p2c[2], pid;
	char buf[10];
	
	pipe(c2p);								//child to parent pipe
	pipe(p2c);								//parent to child pipe
	pid = fork();
	
	if (!pid) 
	{
		write(c2p[1], "Hey", 3);
		close(c2p[1]); 						//close write head
		
		read(p2c[0], buf, 5);
		printf("Parent says %s\n", buf);
		close(p2c[0]); 						//close read head
	}
	else
	{
		read(c2p[0], buf, 3);
		printf("Child says %s\n", buf);
		close(c2p[0]);						//close read head
		
		write(p2c[1], "Hello", 5);
		close(p2c[1]);  					//close write head
		wait();
	}
}
