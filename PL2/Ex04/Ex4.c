#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[]){
	int fd[2],i=0;
	pid_t p;
	FILE* file;
	char ch,writeString[1000],readString[1000];
	char* ptr = writeString;

	file = fopen("data.txt","r");

	if(file==NULL){
		perror("File not found.");
		return 1;
	}

	while((ch=fgetc(file))!=EOF){
		*(ptr+i)=ch;
		i++;
	}

	fclose(file);

	if(pipe(fd)==-1){
		perror("Pipe failed\n");
		return 1;
	}

	p=fork();
	if(p>0){
		close(fd[0]); //closing reading side
		write(fd[1],writeString,1000);
		close(fd[1]); //closing writing side
	}
	if(p==0){
		close(fd[1]); //closing writing side
		read(fd[0], readString, 1000);
		printf("%s\n",readString);
		close(fd[0]); //closing reading side
		exit(0);
	}
	return 0;
}
