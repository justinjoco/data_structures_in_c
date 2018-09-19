#include <stdio.h>
#include <stdlib.h>
#include "packing.h"
#include <string.h>

//Helper function declarations
void destroy_tree(Node *tree);
void perform_packing(Node *tree);
void save_packing_to_file(char* filename, Node* tree);
void print_tree (FILE *out, Node *tree);
void calculate_widths_and_heights(Node *tree);


/*Creates a leaf node. 
*Stores label, width, and height within structure. 
*Everything else is set to 0, '\0' or NULL. 
Returns new leaf node.*/
Node * create_leaf_node(int label, double width, double height){
    Node *leaf = (Node *)malloc(sizeof(Node));
    if (leaf == NULL){
        return NULL;
    }
    leaf->label = label;
    leaf->width = width;
    leaf->height = height;
    leaf->x=0;
    leaf->y=0;
    leaf->letter = '\0';
    leaf->left=NULL;
    leaf->right=NULL;
    leaf->next=NULL;
    return leaf;
}

//Creates a non-leaf node. 
//Stores letter of cutting type. 
//Everything else set to terminating conditions. 
//Returns new non-leaf node.
Node *create_char_node (char letter){
    Node* cut_node = (Node *)malloc(sizeof(Node));
    if (cut_node == NULL){
        return NULL;
    }
    cut_node->label=-1;
    cut_node->width=-1;
    cut_node->height=-1;
    cut_node->x=0;
    cut_node->y=0;
    cut_node->letter = letter;
    cut_node->left=NULL;
    cut_node->right=NULL;
    cut_node->next=NULL;
    return cut_node;

}

/*Prints out a stack. 
If node is a leaf, print out label. 
If node is non-leaf, print out cutting type.*/
void print_stack (Node* stack){
    while (stack !=NULL){
        if (stack->label!=-1){ 
        printf("%d", stack->label);}
        else{
        printf("%c", stack->letter);
        }

        printf("->");
        stack = stack->next;
    }
    printf("NULL\n");
    return;
}

//Push a new node into a stack
Node *push_stack (Node **stack, Node *new){
    if (new==NULL){
        return NULL;
    }
    new->next = *stack;
    *stack = new;
    return new;
}

//Pops the top node from a stack. Passes in node for top of stack to be popped to.
//Returns the top of the updated stack
Node *pop_stack(Node **stack, Node* ret){
    if (stack ==NULL){
        return NULL;
    }
    else{
    Node *ret_node = *stack;
    *stack = ret_node->next;
    ret_node->next = NULL;
   
    *ret = *ret_node;
    free(ret_node);
    return *stack;
   }
}

//Wrapper function that calls functions that actually perform the packing
void perform_packing (Node *tree){
    
     calculate_widths_and_heights(tree);
     get_coordinates(tree);
     return;

}


//Packing Part 1: Calculates the widths and heights of each node within a tree. Postorder
void calculate_widths_and_heights (Node *tree){
    if (tree == NULL){
        return;
    }

    calculate_widths_and_heights(tree->left);
    calculate_widths_and_heights(tree->right);
    
    //Checks if node is a char node
    if (tree->label==-1){


        //Adds widths of children if cut style is vertical
        //Keeps height of tallest child
        if (tree->letter == 'V'){
           tree->width = tree->left->width+tree->right->width; 
           if (tree->left->height>tree->right->height) 
               tree->height=tree->left->height;
           else{ 
               tree->height = tree->right->height;
           }      
           
        }

        //Adds heights of children if cut style is horizontal
        //Keeps width of widest child
        else{
            tree->height = tree->left->height + tree->right->height;
            if (tree->left->width>tree->right->width)
                tree->width = tree->left->width;
         
            else{
                 tree->width = tree->right->width;
            }

        }
    }
}

//Passes in a node pointer and points it to node with highest label. Postorder traversal.
void get_highest_node(Node *tree, Node *highest){
    if (tree == NULL) return;

    get_highest_node(tree->left, highest);
    get_highest_node(tree->right, highest);

    if (tree->label>highest->label){
        *highest = *tree;
    }
    return; 
}

//Packing Part 2: Sets the coordinates of each node based on widths and heights calculated from Part 1. Lots of preorder recursions to update nodes
void get_coordinates(Node *tree){

    if (tree==NULL) {
    return;
    }

    //Checks if node is non-leaf
    if (tree->letter!='\0'){

        //Checks if cut style is vertical
        //Right x-value is the left's x-value + its width
        //Right y-value = Left y-value
        //Updates children of these nodes with the x-value and y-value information
        if (tree->letter=='V'){
            
            tree->right->x=tree->left->x+tree->left->width;
            tree->right->y=tree->left->y;
            tree->left->x=tree->x;    
            tree->left->y=tree->y;        
            get_coordinates(tree->left);   
            get_coordinates(tree->right);
       }
        
        //Checks if cut style is horizontal
        //Left y-value is the right's y-value + its height
        //Left x-value = Right x-value
        //Updates children with x-value and y-value information
        if (tree->letter=='H'){
             tree->left->y=tree->right->y+tree->right->height;
             tree->left->x=tree->right->x;
             tree->right->x=tree->x;
             tree->right->y= tree->y;
             get_coordinates(tree->left);
             get_coordinates(tree->right);
           }

    } 
    get_coordinates(tree->left);
    get_coordinates(tree->right);

    return;
}

//Prints out leaf node information into a given output file. Note that traversal order does not matter since only leaf nodes are printed to file.
void print_tree(FILE *out, Node* tree){
     if (tree == NULL) return;

     print_tree(out, tree->left);
     print_tree(out, tree->right);
     if (tree->label!=-1)
         fprintf(out, "%d %le %le %le %le\n", tree->label, tree->width, tree->height, tree->x, tree->y);

}

//Prints out a node with relevant information
void print_node(Node *node){
    if (node ==NULL){
        printf("NOTHING\n");
    }

    if (node->label!=-1) 
        printf("%d\n", node->label);
    else{
        printf("%c\n",node->letter);
    }

}

//Recursively frees up memory within a stack
void destroy_stack(Node *stack){
    while (stack != NULL){
        Node *temp = stack->next;
        free(stack);
        stack = temp;
    }
    return;
}

//Recursively frees up memory within a tree
void destroy_tree(Node *tree){
    if (tree==NULL)
        return;

    destroy_tree(tree->left);
    destroy_tree(tree->right);
    free(tree);

    return;
}


//Loads a binary tree from a given input file
Node *Load_binary_tree_from_file(char* filename){

    //Open input file
    FILE *readFile = fopen(filename, "r");
    
    //Makes sure input file exists or can be opened
    if (readFile ==NULL){
        fprintf(stderr, "Input file cannot be opened or does not exist.\n");
        return NULL;
    }
 

    //Go to beginning of file
    fseek(readFile, 0, SEEK_SET);
    
    //Make a string without malloc
    char str[40];
    
    //Initialize variables
    int label;
    double width, height;
    char letter;
    Node *header = NULL;
    Node *new = NULL;


   //Read input file line by line
    while (fgets(str, sizeof(str), readFile)!=NULL){  

         //Checks if formatted string is a leaf node
         if (sscanf(str, "%d(%le,%le)\n", &label, &width, &height)!=0){ 

           //Sets a header if it does not exist
           if (header==NULL){                       
               header=create_leaf_node(label, width, height);
           }


           //Pushes leaf node into stack
           else{
               new=create_leaf_node(label, width, height);
               push_stack(&header, new);
           }
        }

        //If it's not a leaf-node, it's a non-leaf node
        else{
            sscanf(str, "%c\n", &letter);
            
            //Sets a header if it does not exist
            if (header == NULL){
                header = create_char_node(letter);
            }

            //If new node is a char node, pop the top two nodes from stack.
            //First pop is right child of new node; Second pop is left child of new node
            //Push new node (with its children) into stack
            else{
                new = create_char_node(letter);
                Node* right = malloc(sizeof(Node));
                Node* left = malloc(sizeof(Node));
                pop_stack(&header, right);
                pop_stack(&header, left);
                new->right = right;
                new->left = left;
                push_stack(&header, new);
            }
          

        }
    }

    //Close input file
    fclose(readFile);

    //Return the binary tree
    return header;

}



//Wrapper function that writes non-leaf nodes of a tree into a file
void save_packing_to_file (char* filename, Node *tree){
    //Open output file
    FILE * outFile = fopen(filename, "w");
    
    //Recursively print tree into output file
    print_tree(outFile, tree);

    //Close output file
    fclose(outFile);
}

