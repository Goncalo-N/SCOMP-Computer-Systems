#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

void letterCaseInverter(char *str){
	int i=0;
	while(str[i]!='\0'){
		if(str[i]>='a'&&str[i]<='z'){
			str[i]=str[i]-32;
		}
		else if(str[i]>='A'&&str[i]<='Z'){
			str[i]=str[i]+32;
		}
		i++;
	}
}

int main(int argc, char *argv[]){
	int up[2],down[2];
	char readMsg[256], writeMsg[256];
	pid_t p;

	printf("Enter the string: ");
	scanf("%s",writeMsg);
	printf("\n");

	if(pipe(up)==-1){
		perror("Pipe failed\n");
		return 1;
	}

	if(pipe(down)==-1){
			perror("Pipe failed\n");
			return 1;
	}

	p=fork();
	if(p>0){
		close(up[1]); //closing writing side on the up pipe
		close(down[0]); //closing reading side on the down pipe
		read(up[0],readMsg,256);
		letterCaseInverter(readMsg);
		write(down[1],readMsg,256);
		close(up[0]); //closing reading side on the up pipe
		close(down[1]); //closing writing side on the down pipe
	}
	if(p==0){
		close(down[1]); //closing writing side on the down pipe
		close(up[0]); //closing reading side on the up pipe
		write(up[1],writeMsg,256);
		read(down[0],writeMsg,256);
		printf("Converted string: %s\n",writeMsg);
		close(up[1]); //closing writing side on the up pipe
		close(down[0]); //closing reading side on the down pipe
	}
	return 0;
}