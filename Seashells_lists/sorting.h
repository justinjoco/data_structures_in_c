#ifndef _SORTING_H_
#define _SORTING_H_

//Define structure Node that stores a long integer and points to another node in a linked list
typedef struct _Node {   
    long value;
    struct _Node *next;
} Node;

//Define structure List that stores a linked-list of linked-lists 
typedef struct _List {
   Node *node;
   struct _List *next;
} List;


//Declare functions in sorting.c file
Node *Load_From_File(char *Filename);     //Loads info from binary file into a linked list

int Save_To_File (char *Filename, Node *list);  //Loads info from a linked list into a binary file

Node *Shell_Sort (Node *list); //Takes a list of long integers and sorts them

#endif

