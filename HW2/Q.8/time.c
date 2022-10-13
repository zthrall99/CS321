/*****************************************************************************
 * time.c                                                                 
 * Name: Zach Thrall
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    const char *name = "v1";
    const int SIZE = 24;
    struct timeval start;
    struct timeval end;
    struct timeval time_passed;
    pid_t pid;
    int shm_fd;
    char *ptr;
    if (argc == 1)
        return 0;
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        printf("shared memory creation failed\n");
        return  -1;
    }
    ftruncate(shm_fd, SIZE);
    ptr = (char *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        printf("memory map failed\n");
        return -1;    
    }
    pid = fork();
    if (pid == 0)
    {
        // child
        if (gettimeofday(&start, NULL) != 0)
            return 0;
        // [FILL UP] write the starting time to shared memory       
   	 memcpy(ptr, &start, sizeof(struct timeval));

        // [FILL UP] now execute the command
        execvp(argv[1], argv + 1);
        fprintf(stderr, "Error");
    }
    else { 
    //parent
        wait(NULL);
    
        if (gettimeofday(&end, NULL) != 0)
            return -1;
        printf("\nParent ending time = %ld sec, %ld microsec\n",end.tv_sec, end.tv_usec);
        
        // [FILL UP] read the starting time from shared memory
    	memcpy(&start, ptr, sizeof(struct timeval));
   	     
        // [FILL UP] now determine elapsed time
    	timersub(&end, &start, &time_passed);
    	printf("Total time passed from start of command: %ld.%06ld\n\n", time_passed.tv_sec, time_passed.tv_usec);
        shm_unlink(name);
    }
    return 0;
}