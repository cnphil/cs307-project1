#include "cse356header.h"
#include "readline.c"
#define MAX_ARGS 50
const char * delim_no_pipe = " \t\n";


void parse_argv(char *buffer, char *argv[])
{
	char *cp = buffer;
	for(int argc = 0; argc < MAX_ARGS; argc++) {
		if((argv[argc] = strtok(cp, delim_no_pipe)) == NULL)
			break;
		cp = NULL;
	}
}


main()
{
	while (true) {
		int argc;
		char *argv[MAX_ARGS];

		write(1, "$ ", 2);
		char buffer[256];
		readline(0, buffer, 255);
		buffer[strlen(buffer) - 1] = '\0'; // get rid of cr
		strcpy(buffer, str_replace(buffer, "~", getenv("HOME")));
		parse_argv(buffer, argv);
		if(strcmp("exit", argv[0]) == 0) exit(0);
		pid_t forkpid;
		forkpid = fork();

		if(forkpid == 0) { // child process 
			execvp(argv[0], argv);
			exit(0);
		}
		wait(NULL);

	}
	exit(0);
}
