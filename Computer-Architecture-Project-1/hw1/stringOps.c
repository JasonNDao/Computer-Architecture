#include <stdio.h>
#include <string.h>

int main(int argc, char*argv[])
{
    if (argv[1]==NULL){
        return 0;
    }
    char **argv2=&argv[1];
    for (int i=0;i<argc-1;i++){
        for (int j=0;j<strlen(argv2[i]);j++){
            char temp[2];
            temp[0]=argv2[i][j];
            temp[1]='\0';
            if (strcmp(temp,"a")==0 || strcmp(temp,"e")==0||strcmp(temp,"i")==0||strcmp(temp,"o")==0||strcmp(temp,"u")==0){
                printf("%s",temp);
                continue;
            }
            if (strcmp(temp,"A")==0 || strcmp(temp,"E")==0||strcmp(temp,"I")==0||strcmp(temp,"O")==0||strcmp(temp,"U")==0){
                printf("%s",temp);
                continue;
            }
        }
    }
    return 0;
}
