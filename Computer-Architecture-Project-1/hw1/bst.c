#include <stdio.h>
#include <stdlib.h>
struct BST{
    int data;
    struct BST *left;
    struct BST * right;
};
struct BST *root=NULL;
void insert(int number){
    struct BST *newnode=(struct BST*)malloc(sizeof(struct BST));
    newnode->data=number;
    newnode->right=NULL;
    newnode->left=NULL;
    if(root==NULL){
        root=newnode;
        return;
    }
    else{
        struct BST *current=root;
        struct BST *previous=NULL;
        while(current != NULL){
            if (current->data > number){
                previous=current;
                current=current->left;
            }
            else if (current->data < number){
                previous=current;
                current=current->right;
            }
            else{
                free(newnode);
                return;
            }
        }
        if (previous->data>number){
            previous->left=newnode;
        }
        else{
            previous->right=newnode;
        }
    }
}
void inorder(struct BST *top){
    if (top==NULL){
        return;
    }
    inorder(top->left);
    printf("%d\t",top->data);
    inorder(top->right);
}

void freeTree(struct BST *top){
    if (top == NULL) {
        return;
    }
    freeTree(top->left); 
    top->left=NULL;
    freeTree(top->right);
    top->right=NULL;
    free(top);
    top=NULL;
}

int main(int argc,char *argv[]){

    if (!fopen(argv[1],"r")){
        printf("error");
        return 0;
    }
    char letter;
    int number;
    FILE *filepointer=fopen(argv[1],"r");
    while (fscanf(filepointer,"%c\t%d\n",&letter,&number)==2)
    {   
        insert(number);
    }
    fclose(filepointer);
    inorder(root);
    freeTree(root);
    root=NULL;
    return 0;
}
