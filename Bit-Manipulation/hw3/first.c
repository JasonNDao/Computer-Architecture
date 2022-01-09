#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc,char **argv){
    if (argc ==1){
        return 0;
    }
    FILE *pointer=fopen(argv[1],"r");
    unsigned short num;
    fscanf(pointer,"%hu",&num);
    char word[5];
    unsigned short num1;
    unsigned short num2;
    while(fscanf(pointer,"%s\t%hu\t%hu\n",word,&num1,&num2)==3){
        if (strcmp(word,"get")==0){
            unsigned short temp=num & (1 << num1);
            temp=temp>>num1; 
            printf("%hu\n",temp);
        }
        if (strcmp(word,"comp")==0){
            num=num ^ (1 << num1);
            printf("%hu\n",num);
        }
        if (strcmp(word,"set")==0){
            unsigned short temp=num & (1 << num1);
            temp=temp>>num1;  
            if (temp==num2){
                printf("%hu\n",num);
                continue;
            }
            else{
                num=num ^ (1 << num1);
                printf("%hu\n",num);
            }
        }
    }
    fclose(pointer);
    return 0;
}
