#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"
#include <string.h>
#include <time.h>
//static void destroy_list(Node *list);
//static void print_list (Node *list);

int main (int argc, char ** argv){

    if (argc != 3)	{	//Check that we have 2 arguments
       
        printf( "You need 2 arguments!\n");
        return EXIT_FAILURE;
    }




    char * inputFile = argv[1];  //Create assignments for input, sequence, and output files
    char * outputFile = argv[2];


  
    double beginning = clock();  //Begin I/O clocking
    Node *longList = Load_From_File (inputFile);  //Load binary file info into a long linked list

    double sortingTime = 0;
 
    double beginSort = clock();  //Begin sort clocking
    longList = Shell_Sort (longList);      //Sort linked list
    double endSort = clock();    //End sort clocking
       
    sortingTime = (double)(endSort-beginSort)/CLOCKS_PER_SEC;  //Calculate insertion sorting time
    
    Save_To_File (outputFile, longList); //Store sorted numbers into a given output binary file
		
    double ending = clock();  //End I/O clocking

    double IOTime = (ending - beginning)/CLOCKS_PER_SEC; //Calculate I/O time
    
    fprintf (stdout,"I/O time: %le\n", IOTime);
    fprintf (stdout,"Sorting time: %le\n", sortingTime);



    return EXIT_SUCCESS;
}
