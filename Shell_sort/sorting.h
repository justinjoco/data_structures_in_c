#ifndef _SORTING_H_
#define _SORTING_H_

//Declares functions in sorting.c file

long *Load_From_File(char *Filename, int *Size);     //Loads info from binary file into a long array

int Save_To_File (char *Filename, long *Array, int Size);  //Loads info from long array into a binary file

void Shell_Insertion_Sort (long *Array, int Size, double *N_Comp, double *N_Move); //Conducts shell insertion sort onto an array

void Shell_Selection_Sort (long *Array, int Size, double *N_Comp, double *N_Move);  //Conducts shell selection sort onto an array

int Print_Seq (char *Filename, int Size);  //Prints out K sequence into a txt file

#endif

