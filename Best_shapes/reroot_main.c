#include <stdio.h>
#include <stdlib.h>
#include "packing.h"

int main (int argc, char **argv){

    //Makes sure there is an input and output file
    if (argc!=3){
        printf("You need to include an input and output file! \n");
        return EXIT_FAILURE;
    }

    //Sets input and output filenames
    char *inputFile = argv[1];
    char *outputFile = argv[2];


    //Loads a binary tree from an input file
    //Assumes input file is in correct format
    Node* tree = Load_binary_tree_from_file(inputFile);
    if (tree == NULL){
        return EXIT_FAILURE;
    }

    
    //Performs packing of tree
    perform_packing(tree);
    
    //Gets node in tree with highest label
    Node *highest = create_char_node('\0');
    get_highest_node(tree, highest);

    //Saves packing to a txt file
    save_packing_to_file(outputFile, tree);
    
  
   // perform_rerooting(tree);

    //Screen dumps info of packing
    fprintf(stdout, "Width: %le\n", tree->width);
    fprintf(stdout, "Height: %le\n", tree->height);
    fprintf(stdout, "X-coordinate: %le\n", highest->x);
    fprintf(stdout, "Y-coordinate: %le\n", highest->y);
     
    //Initialize best width and height variables as original width and heights	
	double best_width = tree->width;
	double best_height = tree->height;

	//Perform rerooting
    perform_rerooting(tree, &best_width, &best_height);

    //Screen dumps rerooting info
    fprintf(stdout, "Best width: %le\n", best_width);
    fprintf(stdout, "Best height: %le\n", best_height);


    //Frees memory in tree
    if (tree!=NULL){
       destroy_tree(tree);
    }

    //Frees pointer to highest label node and best node
    free(highest);


    return EXIT_SUCCESS;
}
