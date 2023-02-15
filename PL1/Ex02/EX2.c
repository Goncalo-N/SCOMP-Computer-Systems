#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {

	printf("I'm..\n");
	pid_t p;

	p = fork();
	if (p==0) printf("I'll never join you!\n");

	else{
		printf("the...\n");

		p = fork();
		if (p==0) printf("I'll never join you!\n");

		else{
			printf("father!\n");

			p = fork();
			if (p==0) printf("I'll never join you!\n");
		}
	}
	return 0;
}
