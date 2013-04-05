#include "cse356header.h" 

main(int argc, char *argv[])
{
	pid_t forkpid;

	timeval start, stop;

	forkpid = fork();
	
	gettimeofday(&start, NULL);
	if(forkpid == 0) {
		execl("./MyCopy", "MyCopy", argv[1], argv[2], NULL);
		exit(0);
	}
	wait(NULL);
	gettimeofday(&stop, NULL);
	printf("MyCopy took %lu\n", stop.tv_usec - start.tv_usec);


	forkpid = fork();
	
	gettimeofday(&start, NULL);
	if(forkpid == 0) {
		execl("./ForkCopy", "ForkCopy", argv[1], argv[2], NULL);
		exit(0);
	}
	wait(NULL);
	gettimeofday(&stop, NULL);
	printf("ForkCopy took %lu\n", stop.tv_usec - start.tv_usec);


	forkpid = fork();
	
	gettimeofday(&start, NULL);
	if(forkpid == 0) {
		execl("./PipeCopy", "PipeCopy", argv[1], argv[2], NULL);
		exit(0);
	}
	wait(NULL);
	gettimeofday(&stop, NULL);
	printf("PipeCopy took %lu\n", stop.tv_usec - start.tv_usec);

	exit(0);
}
