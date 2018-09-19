#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "sorting.h"
#include <math.h>
//Helper Fct Declarations
static Node * Get_K_Seq (int Size);
static Node * construct_Node (long value);
static Node * enqueue (Node *header, Node *new);
static Node * enqueue_sorted (Node *header, Node *temp);
//static void print_list(Node *list);
static void destroy_list(Node *list);
static int getListSize(Node * list);
static Node *reverse_list(Node *list);
static Node *sort_list(Node * list);
static Node *sort_list_with_K(Node * list, int K);
/* ------------------------------------------------------------*/


//Constructs a new node
static Node *construct_Node(long value){
    Node * myNode = (Node*)malloc(sizeof(Node));
    if (myNode == NULL){
        return NULL;
    }
    myNode->value = value;
    myNode->next = NULL;
    return myNode;

}

//Adds a new node into queue
static Node* enqueue(Node *header, Node* new){
    
    //Returns NULL if new is NULL
    if (new==NULL){
        return NULL;
    } 

    //Sets header to new if header is NULL
    if (header == NULL){
        header = new;
        return header;
    }


    //Initializes list pointers
    Node *prev = NULL;
    Node *current = header;

    //Goes to end of linked list
    while (current != NULL){
        prev = current;
        current = current ->next;
    }
    
    //Puts new node at rear of the linked list
    new->next = current;
    if (prev!=NULL){
        prev->next=new;
    }else{
        header = new;
     }   

    //Returns new node
    return new;  

}

//Enqueues some value into a queue in the correct place
static Node * enqueue_sorted(Node *header, Node *temp){
     if (temp==NULL){
         return NULL;

     }

     if (header ==NULL){
        header = temp;
        return temp;
     }
     Node *prev = NULL;
     Node * curr = header;
     
    //Does the same thing as the enqueue function, except that this places the temp value before current value if temp is smaller
     while (curr !=NULL){   
         if (curr->value>=temp->value){
            break;
         }  
          else{ 
          prev = curr;
          curr = curr->next;
          }

     }
     temp->next = curr;
     if (prev!=NULL){
         prev->next=temp;
     }else{
         header=temp;
      }
     return temp;

}

//Commented this function out so compiler won't complain
//Utility function for testing 
/*
static void print_list (Node *list){
    while (list!=NULL){
        printf("%ld", list->value);
        printf("->");
        list = list->next;
    }
    printf("NULL\n");
    return;
}
*/


//Frees up memory allocated in the lists
static void destroy_list (Node * list){
    while (list != NULL){
        Node *temp = list ->next;
        free (list);
        list = temp;
    }
    return;
}


//Gets size of the linked list by traversing through
//the entire list
static int getListSize(Node *list){
    int size = 0;
    Node *curr =list;
    while (curr!=NULL){
        size+=1;
        curr = curr->next;
    }

    return size;
}

//Reverses the order of a linked list
//Used to reverse the K sequence list, which was originally in ascending order
static Node * reverse_list(Node *list){
    
    Node * curr = list;
    Node * prev = NULL;
    Node * next=NULL;
    while (curr!=NULL){
       next = curr ->next;
       curr->next=prev;
       prev = curr;
       curr = next;
    }
     list = prev;
     return list;
}



//Sorts a given list in ascending order
static Node * sort_list(Node *list){
    Node * curr = list->next; //Sets current to the second element in linked list
    Node head;

    head.next=list;  //Keeps track of the head of the list
    Node *temp = NULL;
    Node * prev = list; //Sets prev to first element in list
    head.next->value = prev->value;  //Keeps track of the 1st value in list
    
    //Traverse the list
    while (curr!= NULL){
      
        if (head.next->value>prev->value)
            head.next=prev;                //If a node's value is smaller than the head, set the head to that node
 
        if(prev->value>curr->value){  //Takes out node if that  node's value is bigger than the next.
                                      //Re-stores said node in the list in the correct place
            temp = curr;
            prev->next=curr->next;
            list = enqueue_sorted(head.next, temp);   
            prev = list;
            curr = list->next;

        }

        else{
           prev = curr;
           curr = curr ->next;
        }
    }
    //Return the pointer to the lowest value of the sorted linked list
    return head.next;
}

static Node * sort_list_with_K(Node *list, int K){

    list = sort_list(list);
    return list;

}



/*
 * Converts long integers to be sorted from a binary-format file
 *
 * Size of binary file should determine number of long integers in file
 * Size of binary file should be a multiple of sizeof(long)
 * Allocate sufficient memory to store all long integers in file to an array
 * Assign *Size to the number of integers in said array
 * Returns address of memory allocated for the long integers
 *
 * If file is empty, create linked of size 0
 */

Node *Load_From_File(char *Filename){

    FILE * readFile = fopen(Filename, "r");    //Creates file pointer to input array to read
    if (readFile == NULL){    //Checks if file exists and returns NULL if it doesn't

        fprintf(stderr, "Input file cannot be opened or does not exist.\n");
        return NULL;
    }
    //Gets size of file
    fseek (readFile, 0, SEEK_END);
    long fileSize = ftell(readFile);

    //Go back to file beginning
    fseek (readFile, 0, SEEK_SET);

    //Initialize head of list
     Node *header =NULL;
    
    //Calculate number of integers to be put in array
    int numLongs = fileSize/sizeof(long);
    int i;
    
    //Stores binary info into number
    long number;
    fread(&number, sizeof(long),1,readFile);

    //Construct head of the list
    header = construct_Node(number);
   
    for (i=1; i<numLongs; i++){  //Traverse rest of file and enqueue new nodes into the linked list pointed by header
       fread(&number, sizeof(long), 1, readFile);
       Node * new = construct_Node(number);
       enqueue(header, new);
       
    }  


    // Closes read file
    fclose (readFile);

    //Returns linked list
    return header;

}


/*
 * Saves linked list to an external file specified by Filename in binary format
 *
 * Return number of long integers in the linked list that have been successfully saved in to the file
 *
 * If list size == 0, create an empty file
 */

int Save_To_File (char *Filename, Node *list){
    FILE * writeFile = fopen (Filename, "w"); //Sets file pointer to write to a file
    if (writeFile == NULL){     //Checks if writeFile exists and returns 0 if not
        fprintf(stderr, "Cannot open file!\n");
        return 0; 
   }


    if (list == NULL){  //If linked list is empty, close output file
        fclose(writeFile);
        return 0;
    }

    
    fseek(writeFile, 0, SEEK_SET);
    Node dummy;
    dummy.next = list; //Keeps track of list head
    Node * curr = list;
    Node *prev = NULL;
    long number;
    int numSaved = 0;
    while (curr !=NULL){  //Navigates through linked list and writes each node's value into the file
                          // Keeps track of successful file writes
        number = curr->value;
        numSaved+=fwrite(&number, sizeof(long), 1, writeFile);
        prev = curr;
        curr = curr->next;
    }
 
    //Destroys list once everything's been written   
    destroy_list(dummy.next);
    //Close writeFile
    fclose (writeFile);
    
    //Returns number of integers stored in file
    return numSaved;
}


/*
 * Conducts Shell Insertion Sort on input Array
 */


Node *Shell_Sort (Node *list){
     
   
    int Size = getListSize(list);
    Node * K_list = Get_K_Seq(Size);
    K_list = reverse_list(K_list);
    int K=1;
    list = sort_list_with_K(list, K);

  //  while (curr!=NULL){
  //      K= curr->value;     
  //      list=sort_list_with_K(list, K); 
  //      curr=curr->next;
  //  }
  


    //Destroys K seqeuence list
    if ( K_list!= NULL){       
       destroy_list (K_list);
    }

    //Returns sorted list
    return list;
}



/*
 *Helper function that gets K sequence based on size of array
 *Size is size of long array, and length is size of the K sequence
 *Returns K sequence array
*/


static Node * Get_K_Seq(int Size){
   
    
    //Initialize variables
    int thisNum =0;
    int p,q;
    int rowSum=0;  //Set sum of row exponenets
    Node * Kheader = NULL;
    //While leftmost number in a row is less than Size, continue these loops
    while (pow(2,rowSum) < Size){

        //For each row, initialize exponent of base 2 to rowSum and exponent of base 3 to 0
        for (p=rowSum, q=0; q<=rowSum; p--, q++){  //Increment and decrement p and q by 1 until q equals the row sum
            thisNum = pow(2,p)*pow(3,q);  //Get an element of k sequence by multiplying 2 to the power p by 3 to the power q
            if (thisNum < Size){
            	if (Kheader==NULL)Kheader = construct_Node(thisNum);    //If this particular number of less than size, add number to K sequence list
            	else{
                    Node * new_num = construct_Node(thisNum);
                    enqueue(Kheader, new_num);
                }
            }
        }
        rowSum++;  //Increase row sum
    }
 
    return Kheader;  //Return K array
}


