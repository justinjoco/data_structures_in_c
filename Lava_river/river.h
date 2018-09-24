#ifndef _RIVER_H
#define _RIVER_H

typedef struct _AdjNode{
	int row;
	int col;
	int weight;
	int distance;
	char has_plank;
	struct _AdjNode *predecessor;
	struct _AdjNode *next;
	
	//struct _AdjNode *array;
} AdjNode;

typedef struct _AdjListHead{
	int size;
	AdjNode *head;
	AdjNode adj[8];	
} AdjListHead;

typedef struct _Graph{
	int num_rows;
	int num_cols;
	AdjListHead** matrix;

} Graph;

void cross_the_river(char *filename, int * num_of_turns);


#endif
