#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[]){
	int fd[2], status;
	pid_t p;
	char writeMessage1[] = "Hello World!\n", writeMessage2[] = "Goodbye!\n", readMessage1[100], readMessage2[100];


	if(pipe(fd)==-1){
		perror("Pipe failed\n");
		return 1;
	}

	p=fork();
	if(p>0){
		close(fd[0]); //closing reading side
		write(fd[1],writeMessage1,100);
		write(fd[1],writeMessage2,100);
		close(fd[1]); //closing writing side

		pid_t p2 = wait(&status);
		if(WIFEXITED(status)){
			printf("PID: %d\nExit Value: %d\n",p2,WEXITSTATUS(status));
		}
	}
	if(p==0){
		close(fd[1]); //closing writing side
		read(fd[0], readMessage1, 100);
		printf("Message 1: %s\n",readMessage1);
		read(fd[0], readMessage2, 100);
		printf("Message 2: %s\n",readMessage2);
		close(fd[0]); //closing reading side
		exit(0);
	}
	return 0;
}
