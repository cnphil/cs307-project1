#include "cse356header.h"

main(int argc, char *argv[])
{
	pid_t forkpid;
	int fd[2];

	pipe(fd);
	forkpid = fork();

	if(forkpid == -1) {perror("fork"); exit(1);}
	
	if(forkpid == 0) { // child process, reads 
		close(fd[0]); // closes the input side of the pipe

		FILE *src;

		src  = fopen(argv[1], "r");

		if(src == NULL) {
			printf("Error: Could NOT open file \"%s\".\n", argv[1]);
			exit(-1);
		}
			
		char *buffer[256];
		while (true) {
			int read_chars = fread(buffer, sizeof(char), 255, src);
			if(read_chars <= 0) break;
			write(fd[1], buffer, read_chars);
		}
		fclose(src);
		exit(0);
	} else { // parent process, writes
		close(fd[1]);
		wait(NULL);

		FILE *dest;
			
		dest = fopen(argv[2], "w+");
			
		if(dest == NULL) {
			printf("Error: Could NOT open file \"%s\".\n", argv[2]);
			exit(-1);
		}

		// copying begins
		char *buffer[256];
		while (true) {
			int read_chars = read(fd[0], buffer, sizeof(buffer));
			if(read_chars <= 0) break;
			fwrite(buffer, sizeof(char), read_chars, dest);
		}
		fclose(dest);

		exit(0);
	}
}
