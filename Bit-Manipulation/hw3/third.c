#include <stdlib.h>
#include <stdio.h>

int main(int argc,char **argv){
    if (argc ==1){
        return 0;
    }
    unsigned short temp=(unsigned short)strtol(argv[1],NULL,10);
    int back=15;
    for (int i=0;i<8;i++){
        unsigned short temp2=temp & (1 << i);
        temp2=temp2>>i;
        unsigned short temp3=temp & (1 << back);
        temp3=temp3>>back;
        if (temp2!=temp3){
            printf("Not-Palindrome");
            return 0;
        }
        back--;
    }
    printf("Is-Palindrome");
    return 0;
}
