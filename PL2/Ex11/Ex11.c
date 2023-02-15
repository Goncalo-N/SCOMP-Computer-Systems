#include <stdio.h>
#include <string.h>
#include <sys/types.h> 
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int findGreatestNumber(int a, int b) {
	if(a > b) {
		return a;
	} else if(b > a) {
		return b;
	}
	return a;
}

int main() {
	int i, status, randomNumberParent, randomNumberChild, readNumber, greatestNumber;
	pid_t p;
	int numProcesses = 5, numPipes = 6;
	int fd[numPipes * 2];
	
	randomNumberParent = rand() % 500; 
	printf("PID: %d = %d\n", getpid(), randomNumberParent);
	
	for(i = 0; i < numPipes; i++) {
		if(pipe(fd + i * 2) == -1) {
			perror("Pipe failed\n");
			return 1;
		}
	}
	
	for(i = 0; i < numProcesses; i++) {
		p = fork();
		if(p > 0) { 
			write(*(fd + i * 2 + 1), &randomNumberParent, 4); 
		
			close(*(fd + i * 2 + 1)); 
			
			wait(&status); 
			
			read(*(fd + i * 2), &greatestNumber, 4); 
												
			close(*(fd + i * 2)); 
		
		} else if(p == 0) { 
			randomNumberChild = rand() % 500 + getpid() - 2750; 
			printf("PID: %d = %d\n", getpid(), randomNumberChild);
			
			read(*(fd + i * 2), &readNumber, 4); 
						
			close(*(fd + i * 2)); 
						
			int num = findGreatestNumber(randomNumberChild, readNumber);
			write(*(fd + i * 2 + 1), &num, 4);
					
			close(*(fd + i * 2 + 1)); 
			exit(0);
		}
	}
	
	printf("\nGreatest Number = %d\n", greatestNumber);
	
	return 0;
}