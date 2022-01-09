#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char assembly[100][100];
//char buffer[1000];
int main(int argc, char **argv)
{
    if (argc == 1)
    {
        return 0;
    }
    if (!fopen(argv[1],"r"))
    {
        return 0;
    }
    //setbuf(stdout,buffer);
    int registers[4];
    char temp[100];
    char temp2[100];
    int temp3;
    char temp4[100];
    char temp5[100];
    char temp6[100];
    FILE *pointer = fopen(argv[1], "r");
    int length = 0;
    while (length != 100 && fgets(temp6, 100, pointer) != 0)
    { // load all lines
        if (strcmp(temp6,"\n")==0){
            strcpy(assembly[length],"Noop\n");
        }
        else if (strcmp(temp6,"\r\n")==0){
            strcpy(assembly[length],"Noop\n");
        }
        else{
            strcpy(assembly[length],temp6);
        }
        //printf("%s", assembly[length]);
        length++;
    }
    
    fclose(pointer);
    //printf("\n%d",length);
    int i = 0;
    while (i < length)
    {
        sscanf(assembly[i], "%s\t", temp);
        //printf("%s",assembly[i]);
        int flag1 = 0;
        int flag2 = 0;
        int flag3 = -1;
        if (strcmp(temp, "Noop\n") == 0)
        {
            //Empty line
        }
        if (strcmp(temp, "jmp") == 0)
        {
            sscanf(assembly[i], "%s\t%d", temp, &temp3);
            i = temp3;
            if (length <= i)
            {
                break;
            }
            continue;
        }
        if (strcmp(temp, "je") == 0 || strcmp(temp, "jne") == 0 || strcmp(temp, "jg") == 0 || strcmp(temp, "jge") == 0 || strcmp(temp, "jl") == 0 || strcmp(temp, "jle") == 0)
        {
            sscanf(assembly[i], "%s\t%d\t%s\t%s", temp, &temp3, temp4, temp5);
            if (strcmp(temp4, "ax") == 0)
            {
                flag1 = registers[0];
            }
            else if (strcmp(temp4, "bx") == 0)
            {
                flag1 = registers[1];
            }
            else if (strcmp(temp4, "cx") == 0)
            {
                flag1 = registers[2];
            }
            else if (strcmp(temp4, "dx") == 0)
            {
                flag1 = registers[3];
            }
            else
            {
                flag1 = atoi(temp4);
            }

            if (strcmp(temp5, "ax") == 0)
            {
                flag2 = registers[0];
            }
            else if (strcmp(temp5, "bx") == 0)
            {
                flag2 = registers[1];
            }
            else if (strcmp(temp5, "cx") == 0)
            {
                flag2 = registers[2];
            }
            else if (strcmp(temp5, "dx") == 0)
            {
                flag2 = registers[3];
            }
            else
            {
                flag2 = atoi(temp5);
            }

            if (strcmp(temp, "je") == 0)
            {
                if (flag1 == flag2)
                {
                    i = temp3;
                    if (length <= i)
                    {
                        break;
                    }
                    continue;
                }
            }
            if (strcmp(temp, "jne") == 0)
            {
                if (flag1 != flag2)
                {
                    i = temp3;
                    if (length <= i)
                    {
                        break;
                    }
                    continue;
                }
            }
            if (strcmp(temp, "jg") == 0)
            {
                if (flag1 > flag2)
                {
                    i = temp3;
                    if (length <= i)
                    {
                        break;
                    }
                    continue;
                }
            }
            if (strcmp(temp, "jge") == 0)
            {
                if (flag1 >= flag2)
                {
                    i = temp3;
                    if (length <= i)
                    {
                        break;
                    }
                    continue;
                }
            }
            if (strcmp(temp, "jl") == 0)
            {
                if (flag1 < flag2)
                {
                    i = temp3;
                    if (length <= i)
                    {
                        break;
                    }
                    continue;
                }
            }
            if (strcmp(temp, "jle") == 0)
            {
                if (flag1 <= flag2)
                {
                    i = temp3;
                    if (length <= i)
                    {
                        break;
                    }
                    continue;
                }
            }
        }

        if (strcmp(temp, "add") == 0 || strcmp(temp, "sub") == 0 || strcmp(temp, "mul") == 0 || strcmp(temp, "div") == 0)
        {
            sscanf(assembly[i], "%s\t%s\t%s", temp, temp2, temp4);
            if (strcmp(temp2, "ax") == 0)
            {
                flag1 = registers[0];
            }
            else if (strcmp(temp2, "bx") == 0)
            {
                flag1 = registers[1];
            }
            else if (strcmp(temp2, "cx") == 0)
            {
                flag1 = registers[2];
            }
            else if (strcmp(temp2, "dx") == 0)
            {
                flag1 = registers[3];
            }
            else
            {
                flag1 = atoi(temp2);
            }

            if (strcmp(temp4, "ax") == 0)
            {
                flag2 = registers[0];
                flag3 = 0;
            }
            else if (strcmp(temp4, "bx") == 0)
            {
                flag2 = registers[1];
                flag3 = 1;
            }
            else if (strcmp(temp4, "cx") == 0)
            {
                flag2 = registers[2];
                flag3 = 2;
            }
            else
            {
                flag2 = registers[3];
                flag3 = 3;
            }

            if (strcmp(temp, "add") == 0)
            {
                registers[flag3] = flag1 + flag2;
            }
            if (strcmp(temp, "sub") == 0)
            {
                registers[flag3] = flag2 - flag1;
            }
            if (strcmp(temp, "mul") == 0)
            {
                registers[flag3] = flag1 * flag2;
            }
            if (strcmp(temp, "div") == 0)
            {
                registers[flag3] = flag1 / flag2;
            }
        }
        if (strcmp(temp, "mov") == 0)
        {
            sscanf(assembly[i], "%s\t%s\t%s", temp, temp2, temp4);
            if (strcmp(temp2, "ax") == 0)
            {
                flag1 = registers[0];
            }
            else if (strcmp(temp2, "bx") == 0)
            {
                flag1 = registers[1];
            }
            else if (strcmp(temp2, "cx") == 0)
            {
                flag1 = registers[2];
            }
            else if (strcmp(temp2, "dx") == 0)
            {
                flag1 = registers[3];
            }
            else
            {
                flag1 = atoi(temp2);
            }

            if (strcmp(temp4, "ax") == 0)
            {
                flag3 = 0;
            }
            else if (strcmp(temp4, "bx") == 0)
            {
                flag3 = 1;
            }
            else if (strcmp(temp4, "cx") == 0)
            {
                flag3 = 2;
            }
            else
            {
                flag3 = 3;
            }
            registers[flag3] = flag1;
        }
        if (strcmp(temp, "read") == 0)
        {
            sscanf(assembly[i], "%s\t%s", temp, temp2);
            if (strcmp(temp2, "ax") == 0)
            {
                scanf("%d", &registers[0]);
            }
            else if (strcmp(temp2, "bx") == 0)
            {
                scanf("%d", &registers[1]);
            }
            else if (strcmp(temp2, "cx") == 0)
            {
                scanf("%d", &registers[2]);
            }
            else
            {
                scanf("%d", &registers[3]);
            }
        }
        if (strcmp(temp, "print") == 0)
        {
            sscanf(assembly[i], "%s\t%s", temp, temp2);
            if (strcmp(temp2, "ax") == 0)
            {
                printf("%d", registers[0]);
            }
            else if (strcmp(temp2, "bx") == 0)
            {
                printf("%d", registers[1]);
            }
            else if (strcmp(temp2, "cx") == 0)
            {
                printf("%d", registers[2]);
            }
            else if (strcmp(temp2, "dx") == 0)
            {
                printf("%d", registers[3]);
            }
            else{
                flag1 = atoi(temp2);
                printf("%d",flag1);
            }
        }
        i++;
    }
    return 0;
}
