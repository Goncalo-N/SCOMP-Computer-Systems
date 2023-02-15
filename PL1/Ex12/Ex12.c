#include <stdio.h>

#include <sys/types.h>

#include <unistd.h>

#include <sys/wait.h>

#include <stdlib.h>

#include <stdio.h>

#include <sys/types.h>

#include <unistd.h>



int main(){

    
	int i, status, numProcesses = 6;

    	pid_t p;
	int index = spawn_childs(numProcesses);


  	if(index>0){
       
		exit(index*2);
    
	}
    
	else if(index==0){
        
		for(i=0;i<numProcesses;i++){
            
			p = wait(&status);
            
			if(WIFEXITED(status)){
                
				printf("PID:%d\nExit value:%d\n",p,WEXITSTATUS(status));
            
			}
        
		}
    
	}

    
	return 0;

}



int spawn_childs(int n){
    
	int i;
    
	pid_t p;

    
	for(i=0;i<n;i++){
        
		p = fork();

        
		if(p==0){
            
			return i+1;
        
		}
    
	}
    
	return 0;

}