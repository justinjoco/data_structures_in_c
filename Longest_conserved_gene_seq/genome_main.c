#include <stdio.h>
#include <stdlib.h>
#include "genome.h"

int main (int argc, char ** argv){

    if (argc!=2){
		fprintf(stderr, "You need one input file!\n");
		return EXIT_FAILURE;
	}

    char *inputFile = argv[1];

    int size_of_sequence = 0;
	int *longest_sequence_array = Longest_conserved_gene_sequence(inputFile, &size_of_sequence);

	fprintf(stdout, "Length: %d\n", size_of_sequence);

    if (longest_sequence_array!=NULL){
	    free(longest_sequence_array);
	}


    return EXIT_SUCCESS;
}
