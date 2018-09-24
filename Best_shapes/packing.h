#ifndef _PACKING_H_
#define _PACKING_H_

/*Defines multifunctional node that works as a linked list node and binary tree node. 
   Stores label of leaf node
   Stores cutting type  of non-leaf node
   Stores width and height of rectangle
   Stores x and y coordinates of lower left corner of rectangle
   Stores pointers to a left, right, and next nodes
*/
typedef struct _Node {
    int label;
    char letter;
    double width, height, x, y;
    struct _Node *left;
    struct _Node *right;
    struct _Node *next;
} Node;

//Loads binary tree from file
Node *Load_binary_tree_from_file (char *filename);

//Utility function for testing out stack data
void print_stack (Node *stack);

//Recursively frees up stack
void destroy_stack (Node *stack);


//Prints out leaf node information of a tree into a file
void print_postorder_tree(FILE *out, Node *tree);

//Destroys binary tree
void destroy_tree(Node *tree);

//Pops a node from a stack
Node *pop_stack(Node **stack, Node *ret);

//Prints relevant information of a given node
void print_node(Node *node);

//Packs a tree 
void perform_packing(Node *tree);

//Gets node from tree with highest label
void get_highest_node (Node *tree, Node *highest);

//Creates a non-leaf node
Node *create_char_node(char letter);

//Gets coordinates of nodes within a tree given widths and heights 
void get_coordinates(Node *tree);


//Saves tree packing to a file
void save_packing_to_file (char *filename, Node *tree);

//Perform rerooting
void perform_rerooting (Node *tree,  double *best_width, double *best_height);

#endif
