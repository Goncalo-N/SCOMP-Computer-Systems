#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[]){
	int fd[2], tmp=0, sum=0, vec1[1000], vec2[1000];
	char readMsg[256], writeMsg[256];
	pid_t p;

	for(int i=0;i<1000;i++){
		vec1[i] = rand()%50;
		vec2[i] = rand()%50;
	}

	if(pipe(fd)==-1){
		perror("Pipe failed\n");
		return 1;
	}

	for(int i=0;i<5;i++){
		p=fork();
		if(p==0){
			int min=200*i,max=min+200;
			for(int j=min;j<max;j++){
				tmp+=vec1[j]+vec2[j];
			}
			close(fd[0]); //closing reading side
			write(fd[1],&tmp,4);
			close(fd[1]); //closing writing side
			exit(0);
		}
	}
	for(int i=0;i<5;i++){
		close(fd[1]); //closing writing side
		read(fd[0],&tmp,4);
		sum+=tmp;
	}
	close(fd[1]); //closing reading side
	printf("Result: %d",sum);
	//The read and write funcions already wait for the information so there is no need for another synchronization mechanism such as wait().

	return 0;
}