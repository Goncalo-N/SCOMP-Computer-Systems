#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[]){
	int fd[2];
	pid_t p;
	int writePid, readPid;

	if(pipe(fd)==-1){
		perror("Pipe failed\n");
		return 1;
	}

	p=fork();
	if(p>0){
		close(fd[0]); //closing reading side
		writePid = getpid();
		printf("I am the Father and this is my PID: %d\n", writePid);
		write(fd[1], &writePid, 50);
		close(fd[1]); //closing writing side
	}
	if(p==0){
		close(fd[1]); //closing writing side
		read(fd[0], &readPid, 50);
		printf("I am the Child and I received this PID: %d\n",readPid);
		close(fd[0]); //closing reading side
	}
	return 0;
}
