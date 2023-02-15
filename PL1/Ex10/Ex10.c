#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
	int array[2000], n=13, x=0, results[10], i, j;

	for(i=0;i<2000;i++){
		array[i] = rand()%50;
	}

	for(i=0;i<10;i++){
		if(fork()==0){	
			for(j=0;j<200;j++){
				if(array[j]==n){
					exit(j);
				}
				else{
					exit(255);
				}
			}
		}
		else{
			wait(&x);
			results[i]=x;
			
		}
	}

	for(i=0;i<10;i++){
		printf("\nRange: %d - %d",(200*i),(200*i+200);
	}
}
