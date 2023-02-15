#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[]){
	int fd[2];
	pid_t p;
	int writeNumber, readNumber;
	char writeString[100],readString[100];

	printf("\nEnter the string: ");
	fgets(writeString,100,stdin);
	printf("\nEnter the number: ");
	scanf("%d",&writeNumber);
	printf("\n");

	if(pipe(fd)==-1){
		perror("Pipe failed\n");
		return 1;
	}

	p=fork();
	if(p>0){
		close(fd[0]); //closing reading side
		write(fd[1], writeString, strlen(writeString)+1);
		write(fd[1], &writeNumber, 50);
		close(fd[1]); //closing writing side
	}
	if(p==0){
		close(fd[1]); //closing writing side
		read(fd[0], readString, 100);
		printf("Child received the string: %s\n",readString);
		read(fd[0], &readNumber, 50);
		printf("Child received the number: %d\n",readNumber);
		close(fd[0]); //closing reading side
	}
	return 0;
}
