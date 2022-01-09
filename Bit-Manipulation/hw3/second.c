#include <stdlib.h>
#include <stdio.h>

int main(int argc,char **argv){
    if (argc ==1){
        return 0;
    }
    unsigned short temp=(unsigned short)strtol(argv[1],NULL,10);
    int c=0;
    int c2=0;
    int c3=0;
    for (int i=0;i<16;i++){
        unsigned short temp2=temp & (1 << i);
        temp2=temp2>>i;
        if (temp2==1){
            c3++;
            c2++;
            if (c2==2){
                c++;
                c2=0;
            }
        }
        else{
            c2=0;
        }
    }
    if (c3%2==0){
        printf("Even-Parity\t%d",c);
    }
    else{
        printf("Odd-Parity\t%d",c);
    }
    return 0;
}
