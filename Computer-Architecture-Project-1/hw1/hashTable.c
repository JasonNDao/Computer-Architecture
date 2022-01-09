#include <stdio.h>
#include <stdlib.h>

struct Hash{
    int key;
    int data;
    struct Hash *next;
};
int collision=0;
int ss=0;
struct Hash *hashtable[10000];
void insert(int number){
    struct Hash *newhash=(struct Hash*)malloc(sizeof(struct Hash));
    newhash->data=number;
    newhash->next=NULL;
    while (number<0){
        number+=10000;
    }
    newhash->key=(number % 10000)-1;
    int key=newhash->key;
    if (hashtable[key]==NULL){
        hashtable[key]=newhash;
    }
    else{
        collision++;
        struct Hash *current=hashtable[key];
        while(current->next != NULL){
            current=current->next;
        }
        current->next=newhash;
    }
}
void search(int number){
    int temp=number;
    while (temp<0){
        temp+=10000;
    }
    int index=(temp % 10000)-1;
    if (hashtable[index]==NULL){
        return;
    }
    else{
        struct Hash *current=hashtable[index];
        while(current !=NULL && current->data != number ){
            current=current->next;
        }
        if ( current == NULL){
            return;
        }
        ss++;
    }
}
void clear(){
    for (int i=0;i<10000;i++){
        if (hashtable[i]!=NULL){
            struct Hash * previous=NULL;
            struct Hash *temp=hashtable[i];
            while(temp!=NULL){
                previous=temp;
                temp=temp->next;
                free(previous);
            }
        }
    }
}

int main(int argc,char *argv[]){
    if (!fopen(argv[1],"r")){
        printf("error");
        return 0;
    }
    char letter;
    int number;
    FILE *filepointer=fopen(argv[1],"r");
    while ((fscanf(filepointer,"%c\t%d\n",&letter,&number))==2)
    {    
        if (letter=='s'){
            search(number);
        }
        else{
            insert(number);
        }
    }
    fclose(filepointer);
    printf("%d\n",collision);
    printf("%d",ss);
    clear();
    return 0;
}