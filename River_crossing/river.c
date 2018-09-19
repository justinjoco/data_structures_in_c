#include <stdio.h>
#include <stdlib.h>
#include "river.h"
#include <string.h>
#include <limits.h>
void destroy_list(AdjNode * head, int size);
void destroy_head(AdjListHead * list_head);

//Finds the node with min distance within graph. Adds node into visited list
AdjNode *extract_min (Graph *graph, int visited[graph->num_rows][graph->num_cols]){
	int i,j;
	int min = INT_MAX;
	AdjNode *minNode=NULL;
	for (i=0; i<graph->num_rows; i++){
		for (j=0; j<graph->num_cols;j++){
			if (graph->matrix[i][j].head->distance<min && visited[i][j]==0){
				visited[i][j]=1;
				min = graph->matrix[i][j].head->distance;
				minNode=graph->matrix[i][j].head;	
				
			}
		}
	
	}
	
	return minNode;
	
}

//Finds the shortest path within the graph using Dijkstra's algorithm
int shortest_path(Graph* graph, int src_row, int src_col){

	int path_count = 0;
	int i, j;

	for (i=0; i<graph->num_rows; i++){
		for (j=0; j<graph->num_cols; j++){
			graph->matrix[i][j].head->distance=INT_MAX;
		}
	}

	graph->matrix[src_row][src_col].head->distance=0;
	int visited[graph->num_rows][graph->num_cols];
	for (i=0; i<graph->num_rows;i++){
		for (j=0; j<graph->num_cols; j++){
			visited[i][j]=0;
		
		}
	}
	int dist=0;
	while (1){
		AdjNode *temp = extract_min(graph, visited);
		if (temp==NULL){
			break;
		}
		AdjListHead u = graph->matrix[temp->row][temp->col];
		for (i=0; i<u.size;i++){

			if (graph->matrix[u.adj[i].row][u.adj[i].col].head->distance>u.head->distance+graph->matrix[u.adj[i].row][u.adj[i].col].head->weight){
				graph->matrix[u.adj[i].row][u.adj[i].col].head->distance=u.head->distance+graph->matrix[u.adj[i].row][u.adj[i].col].head->weight;
				
				dist=graph->matrix[u.adj[i].row][u.adj[i].col].head->distance;
			}

		}

	}
		
	
	path_count=dist;
	return path_count;
}


//Create an adjancency node with coordinates, weight, distance, and labels stored.
AdjNode * create_adj_node(int row, int col, char label, int weight){
	AdjNode * node = (AdjNode *)malloc(sizeof(AdjNode));
	node->row = row;
	node->col = col;
	node->weight = weight;
	node->distance = INT_MAX;
	node->has_plank = label;
	node->predecessor=NULL;
	node->next = NULL;
	return node;

}

//Print an adjacency list
void print_list (AdjListHead list, int size){
	int i;
	
	printf("Curr = (%d,%d)\n", list.head->row, list.head->col);
	for (i=0; i<size; i++){
		printf("(%d, %d)%c;%d \n", list.adj[i].row, list.adj[i].col, list.adj[i].has_plank, list.adj[i].weight);

	
	}

}

//Returns an empty 2D array of adjacency lists
AdjListHead ** create_empty_matrix(int num_rows, int num_cols){
	AdjListHead **matrix = (AdjListHead **)malloc(sizeof(AdjListHead*)*num_rows);
	if (matrix == NULL) return NULL;

	int i, j;
	
	//Allocate memory for rows
	for (i=0; i<num_rows; i++){
		matrix[i] = (AdjListHead *)malloc(sizeof(AdjListHead)*num_cols);
		if (matrix[i] == NULL){
			free(matrix);
			return NULL;
		}
	}


	//Initialize each linked list as NULL
	for (i=0; i<num_rows;i++){
		for (j=0; j<num_cols; j++){
			matrix[i][j].head=NULL;
			matrix[i][j].size=0;
		}
	}
	return matrix;
}

//Adds an edge to the graph using an array with src as head

void addEdge(Graph * graph, AdjNode* src, int dest_row, int dest_col, char label, int weight){
//	printf("(%d, %d);%c;%d\n", dest_row, dest_col, label, weight);
	
	int i = graph->matrix[src->row][src->col].size;
	AdjNode * dest = graph->matrix[dest_row][dest_col].head;
	dest->weight=weight;
	
	graph->matrix[src->row][src->col].adj[i]=*dest;
	graph->matrix[src->row][src->col].size++;
}



//Check to see if a node's neighbor exists in eight directions.
//If so, add an edge to that vertex an set weight depending on plank existance
void add_neighbors(Graph* graph, AdjNode *node){

	int weight;
	char label;
	//Upper left
	if (node->row-1>=0 && node->col-1>=0){
		if (graph->matrix[node->row-1][node->col-1].head->has_plank=='1'){
			weight = 1;
			label = '1';
		}
		else{
			weight = 2;
			label='0';
		}
	
		addEdge(graph, node, node->row-1, node->col-1, label, weight);
}

	//Up
	if (node->row-1>=0){
		if (graph->matrix[node->row-1][node->col].head->has_plank=='1'){
			weight = 0;
			label='1';
		}
		else{
			weight =2;
			label='0';
		}

		addEdge(graph, node, node->row-1, node->col, label, weight);
	}
	
	//Upper right
	if (node->row-1>=0 && node->col+1<graph->num_cols){
		if(graph->matrix[node->row-1][node->col+1].head->has_plank=='1'){
			weight = 1;
			label='1';
		}
		else{
			weight = 2;
			label='0';
		}
	
		addEdge(graph, node, node->row-1, node->col+1, label, weight);

	}




	//Right
	if (node->col+1<graph->num_cols){
		if (graph->matrix[node->row][node->col+1].head->has_plank=='1'){
			weight = 1;
			label = '1';
		}
		else{
			weight = 2;
			label='0';
		}
		addEdge(graph, node, node->row, node->col+1, label, weight);

	}


	//Down right
	if (node->row+1<graph->num_rows && node->col+1<graph->num_cols){
		if (graph->matrix[node->row+1][node->col+1].head->has_plank=='1'){
			weight = 1;
			label ='1';
		}
		else{
			weight = 2;
			label='0';
		}
		
		addEdge(graph, node, node->row+1, node->col+1, label, weight);

	}


	//Down
	if (node->row+1<graph->num_rows){
		if (graph->matrix[node->row+1][node->col].head->has_plank=='1'){
			weight = 0;
			label='1';
		}
		else{
			weight = 2;
			label = '0';
		}
		addEdge(graph, node, node->row+1, node->col, label, weight);

	}

	//Down left
	if (node->row+1<graph->num_rows && node->col-1>=0){
		if (graph->matrix[node->row+1][node->col-1].head->has_plank=='1'){
			weight = 1;
			label='1';
		}
		else{
			weight = 2;
			label='0';
		}
		addEdge(graph, node, node->row+1, node->col-1, label, weight);

	}


	//Left
	if (node->col-1>=0){
		if (graph->matrix[node->row][node->col-1].head->has_plank=='1'){
			weight = 1;
			label='1';
		}
		else{
			weight = 2;
			label='0';
		}
		
		addEdge(graph, node, node->row, node->col-1, label, weight);

	}


}

//Wrapper function that creates adjancency lists for each vertex in graph
void create_edge_graph(Graph * graph){
	int i, j;
	for (i=0; i<graph->num_rows; i++){
		for (j = 0; j<graph->num_cols; j++){
			add_neighbors(graph, graph->matrix[i][j].head);				
		
		
		}
	}

	return;
}

//Frees up memory in a linked list
void destroy_list(AdjNode * head, int size){
	while (head != NULL){
         AdjNode *temp = head->next;
         free(head);
         head = temp;
     }
	return;
}

//Creates an empty graph with number of rows and columns filled out
Graph * create_empty_graph(int num_rows, int num_cols){
	Graph * graph = (Graph *)malloc(sizeof(Graph));
	if (graph==NULL){
		return NULL;
	}

	graph->num_rows = num_rows;
	graph->num_cols = num_cols;
	graph->matrix = create_empty_matrix(graph->num_rows, graph->num_cols);
	

	return graph;	

}

//Destroys a character matrix
void destroy_matrix(int num_rows, int num_cols, char ** matrix){
	int i;
	for (i = 0; i<num_rows; i++){
		free(matrix[i]);
	}
	free(matrix);
	return;
}

//Frees up memory stored within a graph
void destroyGraph (Graph * graph){
	int i,j;
	for (i = 0; i<graph->num_rows; i++){
		for (j = 0; j< graph->num_cols; j++){
			destroy_list(graph->matrix[i][j].head, graph->matrix[i][j].size);
		}
		free(graph->matrix[i]);
	}
	free(graph->matrix);
	free(graph);
	return;

}

//Prints the adjacency lists for each vertex in graph
void print_graph(Graph* graph){
	int i,j;
	printf("Number of Rows = %d\t Number of Columns = %d\n",graph->num_rows, graph->num_cols);
	for (j = 0; j<graph->num_cols; j++){
		for (i = 0; i<graph->num_rows; i++){
			print_list(graph->matrix[i][j], graph->matrix[i][j].size);
		}
		printf("\n");
	}
}

//Calculates the least number of turns to cross river
void cross_the_river(char *filename, int * num_of_turns){
	
	FILE *readFile = fopen(filename, "r");

	if (readFile == NULL){
		fprintf(stderr, "Input file cannot be opened or does not exist.\n");
		*num_of_turns = 0;
		return;
	}
	
	fseek(readFile, 0, SEEK_SET);
	
	int num_rows = 0, num_cols = 0;	

	fscanf(readFile, "%d %d\n", &num_rows, &num_cols);
	char ch;
	Graph * graph = create_empty_graph(num_rows-1, num_cols);

	int row_count =0, col_count=0;
	while ((ch = fgetc(readFile))!=EOF){
		if (ch=='\n'){			
			col_count = 0;
			row_count++;
			continue;
		}
		graph->matrix[row_count][col_count].head = create_adj_node(row_count, col_count, ch, 0);	
		col_count++;
	}

	create_edge_graph(graph);	
	
	int shortest = INT_MAX;
	int i=0;
	
	//Conduct Dijkstra's for each coordinate on the starting end
	for (i=0; i<graph->num_rows; i++){ 
		int temp_shortest = shortest_path(graph, i, 0);	
		if (temp_shortest<shortest)
			shortest=temp_shortest;

	}
	*num_of_turns = shortest;
	destroyGraph(graph);
	fclose(readFile);

	return;
}
