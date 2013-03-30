#include "cse356header.h"

main(int argc, char *argv[])
{
	pid_t child_pid;
	int child_status;

	child_pid = fork();

	switch (child_pid) {
		case -1:
			perror("fork");
			exit(1);
		case 0:
			execl("./MyCopy", "MyCopy", argv[1], argv[2], NULL);
			perror("execl() failed!");
		default:
			wait(&child_status);
	}

	exit(0);
}
