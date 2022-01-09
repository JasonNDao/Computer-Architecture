#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Array{
    char name[10];
    int *table;
};

int not(int x)
{
    if (x == 1)
    {
        return 0;
    }
    return 1;
}
int and (int x, int y)
{
    if (x == 1 && y == 1)
    {
        return 1;
    }
    return 0;
}
int or (int x, int y)
{
    if (x == 0 && y == 0)
    {
        return 0;
    }
    return 1;
}
int xor (int x, int y) {
    if (x == y)
    {
        return 0;
    }
    return 1;
}

    int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 0;
    }
    if (!fopen(argv[1], "r"))
    {
        return 0;
    }
    int outnum;
    int lines = 0;
    char *out = (char *)malloc(10 * sizeof(char));
    char *tempy = (char *)malloc(200 * sizeof(char));
    FILE *pointers = fopen(argv[1], "r");  //trying to get output number
    if (fgets(tempy, 200, pointers)==0)           //First line
    {
        return 0;
    }
    if (fgets(tempy, 200, pointers)==0)           //second line
    {
        return 0;
    }
    sscanf(tempy, "%s\t%d", out, &outnum); //get second num value
    while (fgets(tempy, 200, pointers) != 0)
    {
        lines++;
    }
    if (lines==0){
        return 0;
    }
    free(tempy);
    free(out);
    fclose(pointers);

    FILE *pointer = fopen(argv[1], "r");
    int num;
    int twopower;
    char temp[10];
    char tempstuff[3][10]; //circuit instruction names

    if (fscanf(pointer, "%s\t%d", temp, &num) != 2)
    {
        return 0;
    }
    struct Array *vars=(struct Array *)malloc((num + outnum)*sizeof(struct Array)); //names of all input variables
    twopower = pow(2, num);
    for (int i = 0; i < num; i++)
    {
        fscanf(pointer, "%s\t", vars[i].name);
    }
    if (fscanf(pointer, "%s\t%d", temp, &outnum) != 2)
    {
        return 0;
    }
    for (int i = num; i < num + outnum; i++)
    {
        fscanf(pointer, "%s\t", vars[i].name);
    }

    
    int tempnum = twopower;
    int boolean = 0;
    for (int i = 0; i < num; i++) //make truth table values
    {
        vars[i].table=(int *)malloc (twopower*sizeof(int));
        tempnum = tempnum / 2;
        int count = 0;
        for (int j = 0; j < twopower; j++)
        {
            if (count < tempnum)
            {
                vars[i].table[j] = boolean;
                count++;
            }
            else
            {
                if (boolean == 1)
                {
                    boolean = 0;
                }
                else
                {
                    boolean = 1;
                }
                vars[i].table[j] = boolean;
                count = 1;
            }
        }
        boolean = 0;
    }
    for (int j=num;j<num+outnum;j++){
        vars[j].table=(int *)malloc (twopower*sizeof(int));
        for (int i=0;i<twopower;i++){
            vars[j].table[i]=0;
        }
    }
    int **temps = (int **)malloc(twopower*sizeof(int *));
    for (int i = 0; i < twopower; i++)
    {
        temps[i] = (int *)malloc((lines) * sizeof(int));
    }
    char **tempnames = (char **)malloc(lines*sizeof(char *));
    for (int i = 0; i < lines; i++)
    {
        tempnames[i] = (char *)malloc(10 * sizeof(char));
    }
    int tnum = 0;
    int one;
    int two;
    int three;
    boolean = 0;
    while (fscanf(pointer, "%s\t", temp) == 1)
    {
        if (strcmp(temp, "NOT") != 0)
        {
            fscanf(pointer, "%s\t%s\t%s\n", tempstuff[0], tempstuff[1], tempstuff[2]);
            for (int i = 0; i < 3; i++)
            {
                boolean = 0;
                for (int j = 0; j < num + outnum; j++)
                {
                    if (strcmp(tempstuff[i], vars[j].name) == 0)
                    {
                        if (i == 0)
                        {
                            one = j;
                            boolean = 1;
                        }
                        else if (i == 1)
                        {
                            two = j;
                            boolean = 1;
                        }
                        else
                        {
                            three = j;
                            boolean = 1;
                        }
                        break;
                    }
                }
                if (boolean == 1)
                {
                    continue;
                }
                for (int k = 0; k < tnum; k++)
                {
                    if (strcmp(tempstuff[i], tempnames[k]) == 0)
                    {
                        if (i == 0)
                        {
                            one = num + outnum + k;
                            boolean = 1;
                        }
                        else if (i == 1)
                        {
                            two = num + outnum + k;
                            boolean = 1;
                        }
                        else
                        {
                            three = num + outnum + k;
                            boolean = 1;
                        }
                        break;
                    }
                }
                if (boolean == 1)
                {
                    continue;
                }
                strcpy(tempnames[tnum], tempstuff[i]);
                if (i == 0)
                {
                    one = num + outnum + tnum;
                }
                else if (i == 1)
                {
                    two = num + outnum + tnum;
                }
                else
                {
                    three = num + outnum + tnum;
                }
                tnum++;
            }
            int *tempvar1 = (int *)malloc(twopower * sizeof(int));
            int *tempvar2 = (int *)malloc(twopower * sizeof(int));
            int *tempvar3 = (int *)malloc(twopower * sizeof(int));
            if (one > num + outnum - 1)
            {
                for (int i = 0; i < twopower; i++)
                {
                    tempvar1[i] = temps[i][one - num - outnum];
                }
            }
            else
            {
                for (int i = 0; i < twopower; i++)
                {
                    tempvar1[i] = vars[one].table[i];
                }
            }
            if (two > num + outnum - 1)
            {
                for (int i = 0; i < twopower; i++)
                {
                    tempvar2[i] = temps[i][two - num - outnum];
                }
            }
            else
            {
                for (int i = 0; i < twopower; i++)
                {
                     tempvar2[i] = vars[two].table[i];
                }
            }
            if (strcmp("XOR", temp) == 0)
            {
                for (int i = 0; i < twopower; i++)
                {
                    tempvar3[i] = xor(tempvar1[i], tempvar2[i]);
                }
            }
            if (strcmp("AND", temp) == 0)
            {
                for (int i = 0; i < twopower; i++)
                {
                    tempvar3[i] = and(tempvar1[i], tempvar2[i]);
                }
            }
            if (strcmp("OR", temp) == 0)
            {
                for (int i = 0; i < twopower; i++)
                {
                    tempvar3[i] = or (tempvar1[i], tempvar2[i]);
                }
            }
            if (strcmp("NAND", temp) == 0)
            {
                for (int i = 0; i < twopower; i++)
                {
                    tempvar3[i] = not(and(tempvar1[i], tempvar2[i]));
                }
            }
            if (strcmp("NOR", temp) == 0)
            {
                for (int i = 0; i < twopower; i++)
                {
                    tempvar3[i] = not(or (tempvar1[i], tempvar2[i]));
                }
            }

            if (three > num + outnum - 1)
            {
                for (int i = 0; i < twopower; i++)
                {
                    temps[i][three - num - outnum] = tempvar3[i];
                }
            }
            else
            {
                for (int i = 0; i < twopower; i++)
                {
                    vars[three].table[i] = tempvar3[i];
                }
            }
            free(tempvar1);
            free(tempvar2);
            free(tempvar3);
        }
        else
        {
            fscanf(pointer, "%s\t%s\n", tempstuff[0], tempstuff[1]);
            for (int i = 0; i < 2; i++)
            {
                boolean = 0;
                for (int j = 0; j < num + outnum; j++)
                {
                    if (strcmp(tempstuff[i], vars[j].name) == 0)
                    {
                        if (i == 0)
                        {
                            one = j;
                            boolean = 1;
                        }
                        else
                        {
                            two = j;
                            boolean = 1;
                        }
                        break;
                    }
                }
                if (boolean == 1)
                {
                    continue;
                }
                for (int k = 0; k < tnum; k++)
                {
                    if (strcmp(tempstuff[i], tempnames[k]) == 0)
                    {
                        if (i == 0)
                        {
                            one = num + outnum + k;
                            boolean = 1;
                        }
                        else
                        {
                            two = num + outnum + k;
                            boolean = 1;
                        }
                        break;
                    }
                }
                if (boolean == 1)
                {
                    continue;
                }
                strcpy(tempnames[tnum], tempstuff[i]);
                if (i == 0)
                {
                    one = num + outnum + tnum;
                }
                else
                {
                    two = num + outnum + tnum;
                }
                tnum++;
            }
            int *tempvar1 = (int *)malloc(twopower * sizeof(int));
            int *tempvar2 = (int *)malloc(twopower * sizeof(int));
            if (one > num + outnum - 1)
            {
                for (int i = 0; i < twopower; i++)
                {
                    tempvar1[i] = temps[i][one - num - outnum];
                }
            }
            else
            {
                for (int i = 0; i < twopower; i++)
                {
                    tempvar1[i] = vars[one].table[i];
                }
            }
            if (strcmp("NOT", temp) == 0)
            {
                for (int i = 0; i < twopower; i++)
                {
                    tempvar2[i] = not(tempvar1[i]);
                }
            }
            if (two > num + outnum - 1)
            {
                for (int i = 0; i < twopower; i++)
                {
                    temps[i][two - num - outnum] = tempvar2[i];
                }
            }
            else
            {
                for (int i = 0; i < twopower; i++)
                {
                    vars[two].table[i] = tempvar2[i];
                }
            }
            free(tempvar1);
            free(tempvar2);
        }
    }
    fclose(pointer);
    for (int i = 0; i < twopower; i++)
    {
        for (int j = 0; j < num + outnum; j++)
        {
            printf("%d ", vars[j].table[i]);
        }
        printf("\n");
    }

    for (int i = 0; i < twopower; i++)
    {
        free(temps[i]);
    }
    for (int i=0;i<lines;i++){
        free(tempnames[i]);
    }
    for (int i=0;i<num+outnum;i++){
        free(vars[i].table);
    }
    free(temps);
    free(tempnames);
    free(vars);
    return 0;
}