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

int spawn_proc (int in, int out, char *argv[])
{
  pid_t pid;

  if ((pid = fork ()) == 0) {
      if (in != 0) {
          dup2 (in, 0);
          close (in);
      }
      if (out != 1) {
          dup2 (out, 1);
          close (out);
      }

      return execvp (argv [0], argv);
    }

  return pid;
}

main()
{
	while (true) {
		int argc;
		char *argv[MAX_ARGS], *comm[MAX_PIPES];

		write(1, "$ ", 2);
		char buffer[256], buffer2[256];
		readline(0, buffer, 255);
		buffer[strlen(buffer) - 1] = ' '; // get rid of cr
		strcpy(buffer, replace_str(buffer, "~", getenv("HOME")));
		strcpy(buffer2, buffer);
		parse_argv(buffer, argv);
		if(argv[0] != NULL && strcmp("exit", argv[0]) == 0) exit(0);
	
		parse_pipe(buffer2, comm);
		int n;
		for(n = 0; comm[n] != NULL; n++) ;
		int i, in, fd[2];
		in = 0;
		for(i = 0; i < n - 1; i++) {
			pipe(fd);
			parse_argv(comm[i], argv);
			spawn_proc(in, fd[1], argv);
			close(fd[1]);
			in  = fd[0];
		}
		parse_argv(comm[n - 1], argv);
		int last = spawn_proc(in, 1, argv);

		int status;
		waitpid(last, &status, 0);
	}
	exit(0);
}
