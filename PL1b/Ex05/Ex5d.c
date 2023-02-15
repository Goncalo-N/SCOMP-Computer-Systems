#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

void handle_SIGINT(int signo, siginfo_t *sinfo, void *context)
{
	write(STDOUT_FILENO, "I won't let the process end with CTRL-C!", 50);
}

void handle_SIGQUIT(int signo, siginfo_t *sinfo, void *context)
{
	write(STDOUT_FILENO, "I won't let the process end by pressing CLTR-\!", 50);
}

int main(int argc, char *argv[]){
	struct sigaction act;
	struct sigaction act2;
	memset(&act, 0, sizeof(struct sigaction));
	sigemptyset(&act.sa_mask); /* No signals blocked */
	act.sa_sigaction = handle_SIGINT;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act, NULL);
	act2.sa_sigaction = handle_SIGQUIT;
	act2.sa_flags = SA_SIGINFO;
	sigaction(SIGQUIT, &act2, NULL);

	for(;;){
		printf("I Like Signal\n");
		sleep(1);
	}
}