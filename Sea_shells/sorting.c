#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "sorting.h"
#include <math.h>
//Helper Fct Declarations
static int * Get_K_Seq (int Size, int * length);



/*
 * Converts long integers to be sorted from a binary-format file
 *
 * Size of binary file should determine number of long integers in file
 * Size of binary file should be a multiple of sizeof(long)
 * Allocate sufficient memory to store all long integers in file to an array
 * Assign *Size to the number of integers in said array
 * Returns address of memory allocated for the long integers
 *
 * If file is empty, create array of size 0 and *Size = 0
 */

long *Load_From_File(char *Filename, int *Size){

    FILE * readFile = fopen(Filename, "r");    //Creates file pointer to input array to read
    if (readFile == NULL){    //Checks if file exists and returns NULL if it doesn't

        fprintf(stderr, "Input file cannot be opened or does not exist.\n");
        *Size=0;
        return NULL;
    }
    //Gets size of file
    fseek (readFile, 0, SEEK_END);
    long fileSize = ftell(readFile);

    //Go back to file beginning
    fseek (readFile, 0, SEEK_SET);

    //Initialize long array
    long *longArray = NULL;

    //Calculate number of integers to be put in array
    int numLongs = fileSize/sizeof(long);

    //Allocates enough memory to store integer info
    longArray = (long*)malloc(numLongs*sizeof(long));

    //Reads file info into long array
    fread (longArray, sizeof(long), numLongs, readFile);

    //Sets Size to point to an integer that contains number of integers in array
    *Size = numLongs;

    // Closes read file
    fclose (readFile);

    //Returns long array
    return longArray;

}


/*
 * Saves Array to an external file specified by Filename in binary format
 *
 * Return number of long integers in the Array that have been successfully saved in to the file
 *
 * If array size == 0, create an empty file
 */

int Save_To_File (char *Filename, long *Array, int Size){
    FILE * writeFile = fopen (Filename, "w"); //Sets file pointer to write to a file
    if (writeFile == NULL){     //Checks if writeFile exists and returns 0 if not
        fprintf(stderr, "Cannot open file!\n");
        return 0; 
   }


    if (Array == NULL || Size ==0){  //If array is size 0 or is empty, close writeFile and returns 0
        fclose(writeFile);
        return 0;
    }

    //Write long array into given file
    fseek(writeFile, 0, SEEK_SET);
    fwrite (Array, sizeof(long), Size, writeFile);

    //Close writeFile
    fclose (writeFile);
    
    //Returns number of integers stored in file
    return Size;
}


/*
 * Conducts Shell Insertion Sort on input Array
 */
void Shell_Insertion_Sort (long *Array, int Size, double *N_Comp, double *N_Move){
     
    //Get appropriate  K sequence for size of array
    int *seqLen = (int*)malloc(sizeof(int));
    *seqLen=0;
    int * K_array = Get_K_Seq(Size, seqLen);
    
    //Initialize variables for algorithm
    int k_index=0, j=0,i=0, k=0;
    double numComp=0, numMoves=0;
    long temp_r; 


    for (k_index = *seqLen-1; k_index>=0; k_index--){    //Goes through each element within K sequence backwards
        k = K_array[k_index];
        for (j=k; j<Size; j++){           //For each subarray of size k, conduct insertion sort
            temp_r = Array[j];
            i=j;
     

           //While traversing subarray from left to right, if an element is bigger than the one before, swap the two
            while (i>=k && Array[i-k]>temp_r){      
                Array[i] = Array [i-k]; 
                numMoves+=3;
                i = i-k;
            }
            numComp++;
            Array [i] = temp_r;

        }
    }

    *N_Move = numMoves;         //Set number of moves to *N_Move
    *N_Comp = numComp;          //Sets number of comparisons to *N_Comp

    //If K array is filled, free it 
    if (K_array != NULL){       
    free (K_array);
    }

    //Free sequence length
    free(seqLen);
}


/*
 * Conducts Shell Selection Sort on input Array
 */
void Shell_Selection_Sort (long *Array, int Size, double *N_Comp, double *N_Move){

    //Get K Sequence array
    int *seqLen = (int*)malloc(sizeof(int));
    *seqLen=0;
    int *K_array = Get_K_Seq(Size, seqLen);

    //Set algorithm variables
    int k_index=0, j=0,i=0, k=0;
    double numComp=0, numMoves=0;
    int min_index;
    long temp_r;

    //Conduct shell selection sort
    for (k_index = *seqLen-1; k_index>=0; k_index--){  //Go through each element in K sequence backwards
        k = K_array[k_index];
        for (j=k-1; j<Size; j++){  //Go through each subarray of size k
            //Assume smallest element is at index j
            min_index=j;

            //Compare element at index j each element after j
            for (i = j+1; i<Size; i++) {

                //If an element after index j is smaller, set minimum index at that element's location
                if (Array [i] < Array[min_index]){
                    min_index=i;
                    numComp++;
                }

            } 

            //If element after index j is smaller, swap the element at j and the smaller element
            if (min_index != j){
               temp_r = Array[j];
               Array[j]=Array[min_index];
               Array[min_index] = temp_r;
               numMoves+=3;
            }

        }
    }
    //Set number of moves and number of comparisons to respective variables
    *N_Move = numMoves;
    *N_Comp = numComp;
 

    //If K array is not empty, free it
    if (K_array != NULL){
    free (K_array);
    }

    //Free sequence length
    free(seqLen);
}

/*
 *Helper function that gets K sequence based on size of array
 *Size is size of long array, and length is size of the K sequence
 *Returns K sequence array
*/
static int * Get_K_Seq(int Size, int * length){
   
    //Returns nothing if Size is 0 
    if (Size == 0){
       return NULL;
    }
    //Allocate memory to K array
    int * KArray = (int *)malloc(sizeof(int)*Size);
    
    //Initialize variables
    int thisNum =0;
    int p,q;
    int rowSum=0;  //Set sum of row exponenets
    int i = 0;

    //While leftmost number in a row is less than Size, continue these loops
    while (pow(2,rowSum) < Size){

        //For each row, initialize exponent of base 2 to rowSum and exponent of base 3 to 0
        for (p=rowSum, q=0; q<=rowSum; p--, q++){  //Increment and decrement p and q by 1 until q equals the row sum
            thisNum = pow(2,p)*pow(3,q);  //Get an element of k sequence by multiplying 2 to the power p by 3 to the power q
            if (thisNum < Size){
            	KArray[i]=thisNum;    //If this particular number of less than size, add number to K sequence
            	i++;
            }
        }
        rowSum++;  //Increase row sum
    }
 
    *length = i;   //Set *length to number of k added to K array
    return KArray;  //Return K array
}

/*
 *Gets K sequence array from helper function and writes sequence to a txt file
 *Returns length of K sequence array
 */

int Print_Seq (char *Filename, int Size){

    //Sets a txtFile file pointer to write mode
    FILE *txtFile = fopen (Filename, "w");

    //Returns 0 if txtFile fails to open
    if (txtFile == NULL){
        fprintf(stderr, "Cannot open file!\n");
        return 0;

    }

    //If size of long array is 0 or 1, close the txtFile such that file is empty
    if (Size==0||Size==1){
        fclose(txtFile);
        return 0;
    }

    //Go to beginning of txt file
    fseek(txtFile, 0, SEEK_SET);

    //Get K sequence array
    int * lenSeq = (int*)malloc(sizeof(int));
    *lenSeq=0;
    int * seqArray = Get_K_Seq(Size, lenSeq);
    
    //For each element in K sequence, print element into txt file, separated by new lines
    int i;
    for (i = 0 ; i< *lenSeq; i++){
        fprintf(txtFile, "%d\n", seqArray[i]);
    }

    int length = *lenSeq;    //Set length of K array
   
     //Free memory allocated and close txt file
    free(lenSeq);
    free (seqArray);
    fclose(txtFile);

    return length;  //Return length of K sequence array
}

