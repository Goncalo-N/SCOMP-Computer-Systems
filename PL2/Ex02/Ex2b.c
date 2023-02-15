#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[]){
	int fd[2];
	pid_t p;

	struct s{
		char string[100];
		int number;
	}s;

	struct s* writeInfo = &s;
	struct s* readInfo = &s;

	printf("\nEnter the string: ");
	fgets(writeInfo->string,100,stdin);
	printf("\nEnter the number: ");
	scanf("%d",&(writeInfo->number));
	printf("\n");

	if(pipe(fd)==-1){
		perror("Pipe failed\n");
		return 1;
	}

	p=fork();
	if(p>0){
		close(fd[0]); //closing reading side
		write(fd[1], writeInfo, sizeof(s));
		close(fd[1]); //closing writing side
	}
	if(p==0){
		close(fd[1]); //closing writing side
		read(fd[0], readInfo, sizeof(s));
		printf("Child received the string: %s\n",readInfo->string);
		printf("Child received the number: %d\n",readInfo->number);
		close(fd[0]); //closing reading side
	}
	return 0;
}