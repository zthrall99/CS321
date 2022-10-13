/*****************************************************************************
 * zombieCode.c                                                                 
 * Name: Zach Thrall
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//was having issues getting my program to exit properly as well as display 
//any time values in the ps -l command... I was able to create a zombie process though
int main() {
	char message[] = "this child process will become a zombie...\n";
	printf("%s\n", message);

	pid_t pid = fork();
	
	if(pid == 0){
	exit(0);
	}

	sleep(15);
	return 0;	
}