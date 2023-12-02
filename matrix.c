#include <stdio.h>
#include <stdlib.h>

//defining the struct node
struct node{
    int data;
//implementing the right and down pointers
    struct node *right;
    struct node *down;
};
void main(){
//creating the head, current and aboveRow for algorithm to work.
    struct node *head=NULL;
    struct node *current=NULL;
    struct node *aboveRow=NULL;

//b is a counter, a is for reading the input file, c is for reading the commas and /n
    int b=0;
    int a;
    char c;
//opening the files we need, and determining their option as read or write.
    FILE *inputFile = fopen("input.csv","r");
    FILE *outputFile = fopen("output_print.txt","w");
    FILE *diaFile = fopen("output.txt","w");
//if input file is null, it stops compiling and prints an error.
    if(inputFile == NULL){
        printf("Could not open the file.");
        exit(-1);
    }
//a do-while loop for parsing the data from the input.csv file.
    do{
        fscanf(inputFile,"%d",&a);
        struct node* newNode = (struct node*)malloc( sizeof(struct node) );
//creating a new node
        newNode->data = a;
        newNode->right = NULL;
        newNode->down = NULL;
//we apply a statement that connects the head pointer to the first node if head is null.
        if(head == NULL){
            head = newNode;
            current = newNode;
            aboveRow = newNode;
        }
//if head is not null, we can spontaneously add our nodes.
        else{
            if(c==','){
//if the char read is comma, we add our node to the rightmost in row thanks to the while loop :)
                if(current->right!=NULL){
                    while(current->right ==NULL){
                        current= current->right;
                    }
                 }
//in this if statement, the nodes are read until the right node is null, then we add our new node.
                    current->right = newNode;
                    current=current->right;
//if b is not zero, it means that we are not at the first row so that we can determine the aboveRow pointer.
                    if(b!=0){
                    aboveRow=aboveRow->right;
                    aboveRow->down = current;
                    }
        }   else if(c=='\n'){
//we move to the next row if the char is /n. then we increase the integer b by one.
            current =head;
                while(current->down!= NULL){
                    current=current->down;
                }
//placing the aboveRow above the current row (:
                aboveRow=current;
                current->down = newNode;              
                current= current->down;
                b++;
            }
         }
             }while(fscanf(inputFile,"%c",&c)==1);

current = head;
//rest of the code is for printing the outputs. the first while loop is for printing the matrix 
    while (current != NULL) {
        struct node *rowCurrent = current;
        while (rowCurrent->right != NULL) {
            fprintf(outputFile, "%d,", rowCurrent->data);
            rowCurrent = rowCurrent->right;
        }
//I added another fprintf function for the last character in a row not to be a comma.  
        fprintf(outputFile, "%d", rowCurrent->data);

        fprintf(outputFile,"\n");
        current = current->down;
    }
     printf("\n");
    current = head;
//this while loop is for printing the diagonal elements.
     do{     
        fprintf(diaFile, "%d,", current->data);
        current = current->down;
        if(current->down==NULL){
            break;
        }
        current = current->right;
    }while(current!=NULL);
        current = current->right;
        fprintf(diaFile, "%d", current->data);
        fprintf(diaFile,"\n");

    current = head;
//this while loop is for printing the elements from top to the bottom, column by column.
    while (current != NULL) {
        struct node *rowCurrent = current;
        while (rowCurrent != NULL){
            
                fprintf(diaFile, "%d", rowCurrent->data);
//this part is important. for last character in a row not to be comma, i added this if statement. :))

            if(rowCurrent->right==NULL & rowCurrent->down==NULL){
            break;}
            fprintf(diaFile, ",");
            
            rowCurrent = rowCurrent->down;
           
        }
        current = current->right;
    }

//closing the files
fclose(inputFile);
fclose(outputFile);
fclose(diaFile);


}