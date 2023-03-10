#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(void)
{
	int status;
	pid_t p;

	p = fork();

	if(p > 0) // Aqui é o pai!
	{
		wait(&status); // Espera pelo status dada pela função exit do filho
		printf("Output pai filho 1: %d\n", WEXITSTATUS(status));
																
		p = fork();

		if(p == 0) 
		{
			sleep(2); // Adormece durante n segundos
			exit(2);  // Força a saída
		}

		else
		{
			wait(&status); // Espera pelo status dada pela função exit do processo filho
			printf("Output pai filho 2: %d\n", WEXITSTATUS(status)); // WEXITSTATUS(status) Acede ao conteudo
																	 // do apontador do processo filho
		}
	}

	else 
	{
		sleep(1); // Adormece durante n segundos
		exit(1);  //  Força a saída
	}

}