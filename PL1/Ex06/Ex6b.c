#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
	int i;
	int status;

	for(i=0;i<4;i++){
		if(fork()==0){
			sleep(1);
			exit(0);
		}
	}

	printf("This is the end.\n");
}
