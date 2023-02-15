#include <stdio.h>
#include <string.h>
#include <unistd.h>	 
#include <sys/types.h> 
#include <stdlib.h>	   

#define DATABASE_SIZE 5

int main(){	
	int fd[6][2], i, j, ind, exist;
	pid_t pid;
	int barcode;
	
	struct product{
		char name[50];
		float price;
		int barcode;
	};

	for(i = 0; i < 6; i++){
		if(pipe(fd[i]) == -1){
			perror("Pipe failed");
			return 1;
		}
	}

	for(i = 0; i < 5; i++){
		pid = fork();
		if(pid == 0){
			close(fd[0][0]);
			close(fd[i+1][1]);
			printf("Reader %d - Enter Bar Code :\n", i+1);
			scanf("%d", &barcode);
			write(fd[0][1], &barcode, sizeof(int));
			write(fd[0][1], &i, sizeof(int));
			struct product prod;
			read(fd[i+1][0], &prod, sizeof(struct product));
			printf("Reader %d - Name: %s\nPrice: %f\n", i+1, prod.name, prod.price);			
			close(fd[0][1]);
			close(fd[i+1][0]);
			exit(0);
		}
	}
	
	struct product database[DATABASE_SIZE];
	strcpy(database[0].name, "Agua");
	database[0].price = 1.5;
	database[0].barcode = 1;
	strcpy(database[1].name, "Arroz");
	database[1].price = 1.99;
	database[1].barcode = 2;
	strcpy(database[2].name, "Massa");
	database[2].price = 2.20;
	database[2].barcode = 3;
	strcpy(database[3].name, "Atum");
	database[3].price = 1.19;
	database[3].barcode = 4;
	strcpy(database[4].name, "Batata");
	database[4].price = 3;
	database[4].barcode = 5;
	
	for(i = 0; i < 5; i++){
		close(fd[0][1]);
		close(fd[i+1][0]);
		read(fd[0][0], &barcode, sizeof(int));
		read(fd[0][0], &ind, sizeof(int));
		exist = 0;
		for(j = 0; j < DATABASE_SIZE; j++){
			if(barcode == database[j].barcode){
				write(fd[ind+1][1], &database[j], sizeof(struct product));
				exist = 1;
			}				
		}
		if(exist == 0){
			struct product prod;
			strcpy(prod.name, "Product not found.");
			prod.price = 0;
			write(fd[ind+1][1], &prod, sizeof(struct product));
		}
	}
	
	return 0;
}