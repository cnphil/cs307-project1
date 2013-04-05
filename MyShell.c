#include "cse356header.h"
#include "readline.c"
#define MAX_ARGS 50

main()
{
	while (true) {
		int argc;
		char *argv[MAX_ARGS];

		write(1, "$ ", 2);
		char buffer[256];
		readline(0, buffer, 255);
		buffer[strlen(buffer) - 1] = '\0'; // get rid of cr
		if(strcmp("exit", buffer) == 0) exit(0);
		pid_t forkpid;
		forkpid = fork();

		if(forkpid == 0) { // child process 
			argv[0] = buffer; argv[1] = NULL;
			execvp(argv[0], argv);
			exit(0);
		}
		wait(NULL);

	}
	exit(0);
}
