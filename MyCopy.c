#include "cse356header.h"

main(int argc, char *argv[])
{
	FILE *src;

	src  = fopen(argv[1], "r");

	if(src == NULL) {
		printf("Error: Could NOT open file \"%s\".\n", argv[1]);
		exit(-1);
	}
	
	FILE *dest;
	
	dest = fopen(argv[2], "w+");
	
	if(dest == NULL) {
		printf("Error: Could NOT open file \"%s\".\n", argv[2]);
		fclose(src);
		exit(-1);
	}

	// copying begins
	char *buffer[256];
	while (true) {
		int read_chars = fread(buffer, sizeof(char), 255, src);
		if(read_chars <= 0) break;
		fwrite(buffer, sizeof(char), read_chars, dest);
	}
	fclose(src);
	fclose(dest);

	exit(0);
}
