#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

void handle_SIGINT(int signo, siginfo_t *sinfo, void *context)
{
	write(STDOUT_FILENO, "I won't let the process end with CTRL-C!", 50);
}

int main(int argc, char *argv[]){
	struct sigaction act;
	memset(&act, 0, sizeof(struct sigaction));
	sigemptyset(&act.sa_mask); /* No signals blocked */
	act.sa_sigaction = handle_SIGINT;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act, NULL);

	for(;;){
		printf("I Like Signal\n");
		sleep(1);
	}
}
