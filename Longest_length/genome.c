#include <stdio.h>
#include <stdlib.h>
#include "genome.h"
#include <string.h>

static void dfs(Graph * graph, int visited[], int *num, int* counter);

//DFS wrapper function that gets the biggest sequence length from graph's forest
static int DFS(Graph *graph){
	int i,temp_counter;
	int max_counter=0;
	int visited[graph->num_ints];

	for (i=0; i<graph->num_ints;i++){
		visited[i]=0;
	}

	for (i=0; i<graph->num_ints;i++){
	    temp_counter = 0;	
		if (visited[i]!=1){
			int num = i+1;
			dfs(graph, visited, &num, &temp_counter);
	//		continue;
		
		}
	//	for (j=0; j<graph->num_ints;j++){
	//		visited[j]=0;
//		}

		printf("Temp counter = %d\n", temp_counter);
		if (temp_counter>max_counter){
			max_counter=temp_counter;
		}
	}
	return max_counter;
}


//Utility DFS function
//Keeps track of number of branches in this tree
static void dfs(Graph * graph, int visited[], int *num, int * counter){
	//int number = *num-1;
	int i;
	int j;
	*counter=*counter+1;
	visited[*num-1]=1;
	printf("%d\n", *num);


	for (i = 0; i<graph->num_ints; i++){
	//	printf("%d ", i);
		if (visited[i]==0 && graph->edge_matrix[*num-1][i]==1){
	//		 for (j=0; j<graph->num_ints;j++){
		//	     visited[j]=0;
		//	 }
		     *num=i+1;
			// printf("%d \t",*num);
			 dfs(graph, visited, num, counter);
			for (j=i;j<graph->num_ints;j++){
				
				visited[j]=0;
			}			     
		}
	}
	//visited[*num-1]=2;
}

//Utility function used to print out the adjacency matrix
void print_adj_matrix(Graph *  graph){
 	int i, j;
	printf("  ");
	for (i=0; i<graph->num_ints; i++){
		printf("%d ",i+1);
	}
	printf("\n");
	for (i=0; i<graph->num_ints; i++){
          printf("%d ",i+1);
          for (j=0; j<graph->num_ints; j++){
          
		  printf("%d ", graph->edge_matrix[i][j]);
      	  }
		  printf("\n");
	  }

}


//Takes two graphs
//Masks the temp graph's adjacency matrix with that of original
static void AND_graphs (Graph * original, Graph *temp){
	 
	 int i, j;
	 *original->vertex_array=*temp->vertex_array;
	 for (i=0; i<original->num_ints; i++){
        for (j=0; j<original->num_ints; j++){
    
	        if (original->edge_matrix[i][j]==1 && temp->edge_matrix[i][j]==1){
			    original->edge_matrix[i][j]=1;				
			}
			else{
				original->edge_matrix[i][j]=0;
			}
	    }
	  }



}

//Creates adjacency matrix based on input vertex array
static int ** create_adjacency_matrix(int * vertex_array, int num_ints){

	int **matrix = (int**)malloc(sizeof(int*)*num_ints);
	if (matrix == NULL){
	   return NULL;
	
	}

	int i,j;
	for (i=0; i<num_ints; i++){
	    matrix[i]=(int*)malloc(sizeof(int)*num_ints);
		if (matrix[i]==NULL){
		   free(matrix);
		   return NULL;
		}

	}

    for (i=0; i<num_ints;i++){
	    for (j=0; j<num_ints; j++){
		   matrix[i][j]=0;
		
		}
	
	}

	for (i=0; i<num_ints; i++){	
	    for (j=i; j+1<num_ints; j++){

			matrix[vertex_array[i]-1][vertex_array[j+1]-1]=1;
        }
	}

    return matrix;
}


//Creates a graph structure
//Creates a list of vertices from input genome sequence
//Creates an adjacency matrix based on vertex array 
static Graph *createGraph(FILE* readFile, int num_ints){
    Graph * graph = (Graph *)malloc(sizeof(Graph));
	if (graph ==NULL){
	    return NULL;
	}
	
	graph->num_ints=num_ints;
	graph->vertex_array = (int*)malloc(graph->num_ints*sizeof(int));
	if (graph->vertex_array == NULL){
	   free(graph);
	   return NULL;
	}
	
	fread(graph->vertex_array, sizeof(int), graph->num_ints, readFile);
	

    graph->edge_matrix = create_adjacency_matrix(graph->vertex_array, graph->num_ints);	
    if (graph->edge_matrix == NULL){
	    free(graph->vertex_array);
		free(graph);
	    return NULL;
	}

    return graph;

}

//Free memory stored in graph structure
static void destroyGraph(Graph *graph){

    int i;
	for (i=0;i<graph->num_ints;i++){
	    free(graph->edge_matrix[i]);
	}
    free(graph->edge_matrix);
	free(graph->vertex_array);
	free(graph);
	return;
}


int *Longest_conserved_gene_sequence(char* filename, int* size_of_seq){

    FILE *readFile = fopen(filename, "r");

	if (readFile == NULL){
	    fprintf(stderr, "Input file cannot be opened or does not exist\n");
		*size_of_seq = 0;
		return NULL;
	}

    fseek(readFile, 0, SEEK_SET);
    int num_ints, num_sequences;
	//Read number of integers and number of species 
	fread(&num_ints, sizeof(int), 1, readFile);
	fread(&num_sequences, sizeof(int), 1, readFile);

	//Read first integer sequence into a graph structure
    Graph * ret_graph = createGraph(readFile, num_ints);   
    
	//Set a temp graph
    Graph *temp_graph = NULL;
	int i;

	//For every sequence after the first
	//Read sequence into temp graph
	//AND this temp graph's adjacency matrix to that of ret_graph
	//Delete temp matrix

    
	for (i=1; i<num_sequences;i++){
	    temp_graph = createGraph(readFile, num_ints);
		AND_graphs (ret_graph, temp_graph);
        
		destroyGraph(temp_graph);
	
	}

	print_adj_matrix(ret_graph);

	for (i=0; i<ret_graph->num_ints;i++){
		ret_graph->vertex_array[i]=i+1;
	}
	//Conduct DFS unto most updated graph
	int max_counter = DFS(ret_graph);

	
    fclose(readFile);
	if (ret_graph !=NULL){
    	destroyGraph(ret_graph);
	}

	//Set size of sequence as the max counter calculated from DFS
	*size_of_seq = max_counter;


    return NULL;
}

