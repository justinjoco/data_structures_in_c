#ifndef _GENOME_H
#define _GENOME_H

typedef struct _Graph{
    int size;
	int num_ints;
	int ** edge_matrix;
    int * vertex_array;
} Graph;

int *Longest_conserved_gene_sequence(char* filename, int *size_of_seq);

#endif
