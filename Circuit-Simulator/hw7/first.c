#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Array
{
    char name[10];
    int *table;
};
struct Node
{
    char name[10];
    int index;
    int *table;
    struct Node *next;
};
int size = 0;
struct Node *head;
void insert(char *idk, int twopowers)
{
    struct Node *newnode = (struct Node *)malloc(sizeof(struct Node));
    strcpy(newnode->name, idk);
    newnode->index = size;
    newnode->table = (int *)malloc(twopowers * sizeof(int));
    newnode->next = NULL;
    if (size == 0)
    {
        head = newnode;
    }
    else
    {
        struct Node *temp = head;
        struct Node *prev = NULL;
        while (temp != NULL)
        {
            prev = temp;
            temp = temp->next;
        }
        prev->next = newnode;
    }
    size++;
    return;
}
int *search(int number)
{
    struct Node *temp = head;
    while (temp != NULL)
    {
        if (temp->index == number)
        {
            return temp->table;
        }
        temp = temp->next;
    }
    return NULL;
}
struct Node *put(int number)
{
    struct Node *temp = head;
    while (temp != NULL)
    {
        if (temp->index == number)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

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
    char *out = (char *)malloc(10 * sizeof(char));
    char *tempy = (char *)malloc(200 * sizeof(char));
    FILE *pointers = fopen(argv[1], "r"); //trying to get output number
    if (fgets(tempy, 200, pointers) == 0) //First line
    {
        free(tempy);
        free(out);
        fclose(pointers);
        return 0;
    }
    if (fgets(tempy, 200, pointers) == 0) //second line
    {
        free(tempy);
        free(out);
        fclose(pointers);
        return 0;
    }
    if (sscanf(tempy, "%s\t%d", out, &outnum) !=2){ //get second num value
        free(tempy);
        free(out);
        fclose(pointers);
        return 0;
    }
    free(tempy);
    free(out);
    fclose(pointers);

    FILE *pointer = fopen(argv[1], "r");
    int num;
    int twopower;
    char tempp[10];
    char tempstuff[3][10]; //circuit instruction names

    if (fscanf(pointer, "%s\t%d", tempp, &num) != 2)
    {
        fclose(pointer);
        return 0;
    }
    if (num+outnum==0){
        fclose(pointer);
        return 0;
    }
    if (num<0){
        fclose(pointer);
        return 0;
    }
    if (outnum<0){
        fclose(pointer);
        return 0;
    }
    struct Array *vars=(struct Array *)malloc((num + outnum) *sizeof(struct Array)); //names of all input variables
    twopower = pow(2, num);
    for (int i = 0; i < num; i++)
    {
        fscanf(pointer, "%s\t", vars[i].name);
    }
    if (fscanf(pointer, "%s\t%d", tempp, &outnum) != 2)
    {
        free(vars);
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
        vars[i].table = (int *)malloc(twopower * sizeof(int));
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
    for (int j = num; j < num + outnum; j++)
    {
        vars[j].table = (int *)malloc(twopower * sizeof(int));
        for (int i = 0; i < twopower; i++)
        {
            vars[j].table[i] = 0;
        }
    }

    int one;
    int two;
    int three;
    boolean = 0;
    while (fscanf(pointer, "%s\t", tempp) == 1)
    {
        if (strcmp(tempp, "NOT") != 0)
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
                for (struct Node *temp = head; temp != NULL; temp = temp->next)
                {
                    if (strcmp(tempstuff[i], temp->name) == 0)
                    {
                        if (i == 0)
                        {
                            one = num + outnum + temp->index;
                            boolean = 1;
                        }
                        else if (i == 1)
                        {
                            two = num + outnum + temp->index;
                            boolean = 1;
                        }
                        else
                        {
                            three = num + outnum + temp->index;
                            boolean = 1;
                        }
                        break;
                    }
                }
                if (boolean == 1)
                {
                    continue;
                }
                insert(tempstuff[i], twopower);
                if (i == 0)
                {
                    one = num + outnum + size - 1;
                }
                else if (i == 1)
                {
                    two = num + outnum + size - 1;
                }
                else
                {
                    three = num + outnum + size - 1;
                }
            }
            int *tempvar1 = (int *)malloc(twopower * sizeof(int));
            int *tempvar2 = (int *)malloc(twopower * sizeof(int));
            int *tempvar3 = (int *)malloc(twopower * sizeof(int));
            if (one > num + outnum - 1)
            {
                for (int i = 0; i < twopower; i++)
                {
                    tempvar1[i] = search(one - num - outnum)[i];
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
                    tempvar2[i] = search(two - num - outnum)[i];
                }
            }
            else
            {
                for (int i = 0; i < twopower; i++)
                {
                    tempvar2[i] = vars[two].table[i];
                }
            }
            if (strcmp("XOR", tempp) == 0)
            {
                for (int i = 0; i < twopower; i++)
                {
                    tempvar3[i] = xor(tempvar1[i], tempvar2[i]);
                }
            }
            if (strcmp("AND", tempp) == 0)
            {
                for (int i = 0; i < twopower; i++)
                {
                    tempvar3[i] = and(tempvar1[i], tempvar2[i]);
                }
            }
            if (strcmp("OR", tempp) == 0)
            {
                for (int i = 0; i < twopower; i++)
                {
                    tempvar3[i] = or (tempvar1[i], tempvar2[i]);
                }
            }
            if (strcmp("NAND", tempp) == 0)
            {
                for (int i = 0; i < twopower; i++)
                {
                    tempvar3[i] = not(and(tempvar1[i], tempvar2[i]));
                }
            }
            if (strcmp("NOR", tempp) == 0)
            {
                for (int i = 0; i < twopower; i++)
                {
                    tempvar3[i] = not(or (tempvar1[i], tempvar2[i]));
                }
            }

            if (three > num + outnum - 1)
            {
                struct Node *destruct;
                destruct = put(three - num - outnum);
                for (int i = 0; i < twopower; i++)
                {
                    destruct->table[i] = tempvar3[i];
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
                for (struct Node *temp = head; temp != NULL; temp = temp->next)
                {
                    if (strcmp(tempstuff[i], temp->name) == 0)
                    {
                        if (i == 0)
                        {
                            one = num + outnum + temp->index;
                            boolean = 1;
                        }
                        else
                        {
                            two = num + outnum + temp->index;
                            boolean = 1;
                        }
                        break;
                    }
                }
                if (boolean == 1)
                {
                    continue;
                }
                insert(tempstuff[i], twopower);
                if (i == 0)
                {
                    one = num + outnum + size - 1;
                }
                else
                {
                    two = num + outnum + size - 1;
                }
            }
            int *tempvar1 = (int *)malloc(twopower * sizeof(int));
            int *tempvar2 = (int *)malloc(twopower * sizeof(int));
            if (one > num + outnum - 1)
            {
                for (int i = 0; i < twopower; i++)
                {
                    tempvar1[i] = search(one - num - outnum)[i];
                }
            }
            else
            {
                for (int i = 0; i < twopower; i++)
                {
                    tempvar1[i] = vars[one].table[i];
                }
            }
            if (strcmp("NOT", tempp) == 0)
            {
                for (int i = 0; i < twopower; i++)
                {
                    tempvar2[i] = not(tempvar1[i]);
                }
            }
            if (two > num + outnum - 1)
            {
                struct Node *destruct;
                destruct = put(two - num - outnum);
                for (int i = 0; i < twopower; i++)
                {
                    destruct->table[i] = tempvar2[i];
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

    struct Node *prev = NULL;
    for (struct Node *temp = head; temp != NULL; temp = temp->next)
    {
        if (prev != NULL)
        {
            free(prev);
        }
        prev = temp;
        free(temp->table);
    }
    if (prev != NULL)
    {
        free(prev);
    }
    for (int i = 0; i < num + outnum; i++)
    {
        free(vars[i].table);
    }
    free(vars);
    return 0;
}