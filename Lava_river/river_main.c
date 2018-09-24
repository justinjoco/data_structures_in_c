#include <stdio.h>
#include <stdlib.h>
#include "river.h"

int main(int argc, char **argv){

	if (argc!=2){
		fprintf(stderr, "You need one input file!\n");
		return EXIT_FAILURE;
	}

	char *input = argv[1];
	int num_of_turns = 0;

	cross_the_river(input, &num_of_turns);

	printf("%d\n", num_of_turns);


	return EXIT_SUCCESS;
}
