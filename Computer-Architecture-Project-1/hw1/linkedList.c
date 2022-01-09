#include <stdio.h>
#include <stdlib.h>

int size = 0;
struct Node{
    int data;
    struct Node *next;
};
struct Node *head;
void insert(int number){
    struct Node *newnode = (struct Node *)malloc(sizeof(struct Node));
    newnode->data = number;
    newnode->next = NULL;
    if (size == 0){
        head = newnode;
        newnode->next = NULL;
    }
    else
    {
        struct Node *previous = NULL;
        struct Node *pointer = head;
        while (pointer != NULL && ((pointer->data) < (newnode->data))){
            previous = pointer;
            pointer = pointer->next;
        }
        if (previous == NULL){
            newnode->next = head;
            head = newnode;
        }
        else if (pointer == NULL){
            previous->next = newnode;
        }
        else{
            newnode->next = previous->next;
            previous->next = newnode;
        }
        previous=NULL;
        pointer=NULL;
    }
    size++;
}
void print(){
    printf("%d\n",size);
    if (head != NULL){
        struct Node *previous = NULL;
        struct Node *pointer = head;
        while (pointer!=NULL){
            if ((previous == NULL && pointer!= NULL)||(previous != NULL && previous->data!=pointer->data)){  
                printf("%d\t", pointer->data);
            }
            previous=pointer;
            pointer = pointer->next;
        }
    }
}
void delete (int number){
    struct Node *previous = NULL;
    struct Node *pointer = head;
    while (pointer != NULL && ((pointer->data) < number)){
        previous = pointer;
        pointer = pointer->next;
    }
    if (previous==NULL && pointer != NULL && pointer->data==number){
        head=pointer->next;
        pointer->next=NULL;
        free(pointer);
        size--;
        return;
    }
    if(pointer != NULL && pointer->data==number){
        previous->next=pointer->next;
        pointer->next=NULL;
        free(pointer);
        size--;
        return;
    }
}

void freeList(struct Node* top)
{
   struct Node* temp;

   while (top != NULL)
    {
       temp = top;
       top = top->next;
       free(temp);
    }

}

int main(int argc, char *argv[]){
    if(fopen(argv[1],"r")==NULL){
        printf("error");
        return 0;
    }
    char letter;
    int number;
    FILE *filepointer=fopen(argv[1],"r");
    while (fscanf(filepointer,"%c\t%d\n",&letter,&number)==2){  
        if (letter=='d'){
            delete(number);
        }
        else{
            insert(number);
        }
    }
    fclose(filepointer);
    print();
    freeList(head);
    return 0;
}