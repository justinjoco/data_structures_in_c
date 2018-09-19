#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"
#include <string.h>
#include <time.h>

//#define CLOCKS_PER_SECOND = 1000000000;

int main (int argc, char ** argv){

    if (argc != 5)	{			//CHeck that we have 4 arguments
       
        printf( "You need 4 arguments!\n");
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "s" ) != 0 && strcmp(argv[1], "i" ) != 0){   //Make sure a valid sorting method is entered


        printf ("Invalid sorting method!\n");
        return EXIT_FAILURE;
    }

    char * inputFile = argv[2];  //Create assignments for input, sequence, and output files
    char * seqFile = argv[3];
    char * outputFile = argv[4];

    int * Size = (int*)malloc(sizeof(int));  //Assigns Size to point to an address of type int

  
    double beginning = clock();  //Begin I/O clocking
    long * longArray = Load_From_File (inputFile, Size);  //Load binary file info into a long array


    //Allocate memory to create N_Comp and N_Move variables to point to addresses of type int, and setting those ints to 0.
    double *N_Comp = (double*)malloc(sizeof(double));
    *N_Comp=0;

    double *N_Move = (double*)malloc(sizeof(double));
    *N_Move=0;

    //Set a sortingTime variable so compiler won't complain
    double sortingTime = 0;
    if (strcmp (argv[1], "i") == 0){  //Sorts long array through shell insertion sort if 1st arg is 'i'
 
   //    printf("SHELL INSERTION SORT\n");
       double beginSort = clock();  //Begin sort clocking
       Shell_Insertion_Sort (longArray, *Size, N_Comp, N_Move);
       double endSort = clock();    //End sort clocking
       
       sortingTime = (double)(endSort-beginSort)/CLOCKS_PER_SEC;  //Calculate insertion sorting time
    }
    
    else{                             //Sorts long array through shell selection srt if 1st arg is 's'

    //    printf("SHELL SELECTION SORT\n");
        double beginSort = clock();  //Begin sort clocking
        Shell_Selection_Sort (longArray, *Size, N_Comp, N_Move);
        double endSort = clock();    //End sort clocking
    
        sortingTime = (double)(endSort - beginSort)/ CLOCKS_PER_SEC;  //Calculate selection sorting time
    }
	
    int lenShellSeq = Print_Seq (seqFile, *Size); //Prints out the K sequence into a given txt file

    int numLongStored = Save_To_File (outputFile, longArray, *Size); //Store sorted numbers into a given output binary file
		

    double ending = clock();  //End I/O clocking

    double IOTime = (ending - beginning)/CLOCKS_PER_SEC; //Calculate I/O time


    // Print out sorting and I/O information to standard output
    fprintf (stdout,"Number of long integers read: %d\n", *Size);
    fprintf (stdout,"Number of long integers stored: %d\n", numLongStored);
    fprintf (stdout,"Length of sequence: %d\n", lenShellSeq);
    fprintf (stdout,"Number of comparisons: %le\n", *N_Comp);
    fprintf (stdout,"Number of moves: %le\n", *N_Move);
    fprintf (stdout,"I/O time: %le\n", IOTime);
    fprintf (stdout,"Sorting time: %le\n", sortingTime);



    //Free memory allocated from before
    free (longArray);
    free (Size);
    free (N_Move);
    free (N_Comp);


    return EXIT_SUCCESS;
}
