#include "cse356header.h"
#include "readline.c"
#define MAX_ARGS 50
#define MAX_PIPES 50
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

void parse_pipe(char *buffer, char *argv[])
{
	char *cp = buffer;
	for(int argc = 0; argc < MAX_PIPES; argc++) {
		if((argv[argc] = strtok(cp, "|")) == NULL)
			break;
		cp = NULL;
	}
}

struct pair {
	int n[2];
};

main()
{
	while (true) {
		int argc;
		char *argv[MAX_ARGS], *comm[MAX_PIPES];

		write(1, "$ ", 2);
		char buffer[256], buffer2[256];
		readline(0, buffer, 255);
		buffer[strlen(buffer) - 1] = '\0'; // get rid of cr
		strcpy(buffer, replace_str(buffer, "~", getenv("HOME")));
		strcpy(buffer2, buffer);
		parse_argv(buffer, argv);
		if(strcmp("exit", argv[0]) == 0) exit(0);
	
		pair pipefd;
		pipe(pipefd.n);
		parse_pipe(buffer2, comm);
		for(int i = 0; comm[i] != NULL; i++) {
			write(1, "\"", 1);
			write(1, comm[i], strlen(comm[i]));
			write(1, "\"", 1);
			if(fork() == 0) {
				if(i != 1) {dup2(pipefd.n[1], 1); close(pipefd.n[0]);}
				if(i != 0) {dup2(pipefd.n[0], 0); close(pipefd.n[1]);}
				parse_argv(comm[i], argv);
				execvp(argv[0], argv);
				perror("exec failed");
				exit(1);
			}
			write(1, "IN", 2);
			wait(NULL);
			write(1, "OUT", 3);
		}
	}
	exit(0);
}
