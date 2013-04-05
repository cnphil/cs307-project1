#include "cse356header.h"

main(int argc, char *argv[]) {
    int pipefd[2];
    pid_t ls_pid, wc_pid;

    pipe(pipefd);

    // this child is generating output to the pipe
    //
    if ((ls_pid = fork()) == 0) {
        // attach stdout to the left side of pipe
        // and inherit stdin and stdout from parent
        dup2(pipefd[1],STDOUT_FILENO);
        close(pipefd[0]);              // not using the right side

		char *lsargs[] = {"ls", "-l", NULL};
        execvp("/bin/ls", lsargs);
        perror("exec ls failed");
        exit(EXIT_FAILURE);
    } 
	wait(NULL);
    // this child is consuming input from the pipe
    //
    if ((wc_pid = fork()) == 0) {
        // attach stdin to the right side of pipe
        // and inherit stdout and stderr from parent
        dup2(pipefd[0], STDIN_FILENO);

        close(pipefd[1]);              // not using the left side
        char *wcargs[] = {"wc", NULL};
		execvp("wc", wcargs);
        perror("exec wc failed");
        exit(EXIT_FAILURE);
    }
	
    // explicitly not waiting for ls_pid here
    // wc_pid isn't even my child, it belongs to ls_pid

    return EXIT_SUCCESS;
}

