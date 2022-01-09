#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

long long int read = 0;      //counter for read
long long int write = 0;     //counter for write
long long int miss = 0;      //counter for miss
long long int hit = 0;       //counter for hit
long long int realcount = 0; // puts a count to see last visited
long long int sets = 0;      //number of set block (actual)
int setsz = 0;               //number of blocks bit
char assoc[10];              //keep what assoc it is
long long int assoc2 = 1;
char replace[10]; // keep what replace policy it is

int getpower(long long int x)
{ //get power of two
    long long int temp = 1LL;
    if (x < temp)
    {
        return -1;
    }
    if (x == temp)
    {
        return 0;
    }
    int count = 0;
    while (temp < x)
    {
        temp = temp * 2;
        count++;
        if (temp == x)
        {
            return count;
        }
    }
    return -1;
}
int poweroftwo(long long int x)
{ //check if power of two
    if (x <= 0)
    {
        return 0;
    }
    long long int temp = 1LL;
    for (long long int i = 0; i < x; i++)
    {
        if (temp >x){
            break;
        }
        if (x==temp){
            return 1;
        }
        temp = temp * 2;

    }
    return 0;
}

int checkint(char temp[])
{ //check if int
    for (int i = 0; i < strlen(temp); i++)
    {
        if (!isdigit(temp[i]))
        {
            return 0;
        }
    }
    return 1;
}

int checkassoc(char temp[])
{ //check if assoc:n
    char temp2[] = "assoc:";
    if (strlen(temp) <= strlen(temp2))
    {
        return 0;
    }
    for (int i = 0; i < strlen(temp2); i++)
    {
        if (temp[i] != temp2[i])
        {
            return 0;
        }
    }
    char temp3[strlen(temp) - strlen(temp2) + 1]; //print that out to test
    for (int i = 6; i < strlen(temp); i++)
    {
        char temp5[2];
        temp5[0] = temp[i];
        temp5[1] = '\0';
        if (i == 6)
        {
            strcpy(temp3, temp5);
        }
        else
        {
            strcat(temp3, temp5);
        }
    }
    if (checkint(temp3) == 0)
    {
        return 0;
    }
    else
    {
        assoc2 = atoll(temp3);
    }
    if (poweroftwo(assoc2) == 0)
    {
        return 0;
    }
    else
    {
        sets = sets / assoc2;
    }
    return 1;
}
long long int power(int x)
{
    long long int temp = 1LL;
    for (int i = 0; i < x; i++)
    {
        temp = temp * 2;
    }
    return temp;
}
int main(int argc, char *argv[])
{
    if (argc != 6)
    { //check for 6 arguments
        printf("error\n");
        return 0;
    }

    if (checkint(argv[1]) == 0 || checkint(argv[4]) == 0)
    { //check of block size and cache size are int inputs
        printf("error\n");
        return 0;
    }
    long long int cachesz = atoll(argv[1]); //if are, convert them to ints
    long long int blocksz2 = atoll(argv[4]);
    if (poweroftwo(cachesz) == 0 || poweroftwo(blocksz2) == 0)
    { //check if power of two,if not quit
        printf("error\n");
        return 0;
    }
    sets = cachesz / blocksz2;        //get num lines
    int blocksz = getpower(blocksz2); //block bit size

    if (strcmp(argv[3], "lru") == 0 || strcmp(argv[3], "fifo") == 0)
    { //check if replace policy is correct and records it
        strcpy(replace, argv[3]);
    }
    else
    {
        printf("error\n");
        return 0;
    }

    if (strcmp(argv[2], "direct") == 0 || strcmp(argv[2], "assoc") == 0)
    { //check if replace policy is correct and records it
        strcpy(assoc, argv[2]);
        setsz = getpower(sets); //set bit size
        if (sets < 1)
        {
            printf("error\n");
            return 0;
        }
        if (strcmp(argv[2], "assoc") == 0)
        {
            setsz = 0;
        }
    }
    else
    { //if n assoc- records n if n is valid
        if (checkassoc(argv[2]) == 0)
        {
            printf("error\n");
            return 0;
        }
        setsz = getpower(sets); //set bit size
        if (sets < 1)
        {
            printf("error\n");
            return 0;
        }
        strcpy(assoc, "other");
    }

    if (!fopen(argv[5], "r"))
    { //check if file exists
        printf("error\n");
        return 0;
    }
    int tagsz = 48 - blocksz - setsz;

    long long int record[sets][assoc2]; //cache to record which one to evict
    long long int cache[sets][assoc2];  //cache to record memory addresses
    for (long long int i = 0; i < sets; i++)
    {
        for (long long int j = 0; j < assoc2; j++)
        {
            cache[i][j] = -1;
        }
    }
    char rw;               //read or write recorder
    long long int address; //records address
    char throwaway[50];    //temp
    char throwaway2[50];   //temp to make hex into string and then later into address

    long long int seti; //records set number it belongs to
    long long int tagi; //records tag number

    long long int leastcount; //number to record which to evict
    long long int recordi;
    FILE *pointer = fopen(argv[5], "r");
    while (strcmp(assoc, "direct") == 0 || strcmp(assoc, "other") == 0)
    {
        if (fscanf(pointer, "%s\t%c\t%s\n", throwaway, &rw, throwaway2) != 3)
        {
            break;
        }
        address = (long long int)strtoll(throwaway2, NULL, 16);
        seti = (address >> blocksz) & (power(setsz) - 1);
        tagi = (address >> (blocksz + setsz)) & (power(tagsz) - 1);
        for (long long int i = 0; i < assoc2; i++)
        {
            if (i == 0)
            {
                leastcount = record[seti][i];
                recordi = i;
            }
            if (cache[seti][i] == -1)
            {
                miss++;
                read++;
                if (rw == 'W' || rw == 'w')
                {
                    write++;
                }
                cache[seti][i] = tagi;
                record[seti][i] = realcount;
                break;
            }
            if (cache[seti][i] == tagi)
            {
                if (strcmp(replace, "lru") == 0)
                {
                    record[seti][i] = realcount;
                }
                if (rw == 'W' || rw == 'w')
                {
                    write++;
                }
                hit++;
                break;
            }
            if (record[seti][i] < leastcount)
            {
                leastcount = record[seti][i];
                recordi = i;
            }
            if (i == assoc2 - 1)
            {
                cache[seti][recordi] = tagi;
                record[seti][recordi] = realcount;
                miss++;
                read++;
                if (rw == 'W' || rw == 'w')
                {
                    write++;
                }
            }
        }
        realcount++;
    }
    while (strcmp(assoc, "assoc") == 0)
    {
        if (fscanf(pointer, "%s\t%c\t%s\n", throwaway, &rw, throwaway2) != 3)
        {
            break;
        }
        address = (long long int)strtoll(throwaway2, NULL, 16);
        tagi = (address >> (blocksz)) & (power(tagsz) - 1);
        for (long long int i = 0; i < sets; i++)
        {
            if (i == 0)
            {
                leastcount = record[i][0];
                recordi = i;
            }
            if (cache[i][0] == -1)
            {
                miss++;
                read++;
                if (rw == 'W' || rw == 'w')
                {
                    write++;
                }
                cache[i][0] = tagi;
                record[i][0] = realcount;
                break;
            }
            if (cache[i][0] == tagi)
            {
                if (strcmp(replace, "lru") == 0)
                {
                    record[i][0] = realcount;
                }
                if (rw == 'W' || rw == 'w')
                {
                    write++;
                }
                hit++;
                break;
            }
            if (record[i][0] < leastcount)
            {
                leastcount = record[i][0];
                recordi = i;
            }
            if (i == sets - 1)
            {
                cache[recordi][0] = tagi;
                record[recordi][0] = realcount;
                miss++;
                read++;
                if (rw == 'W' || rw == 'w')
                {
                    write++;
                }
            }
        }
        realcount++;
    }
    fclose(pointer);
    printf("Memory reads: %lld\n", read);
    printf("Memory writes: %lld\n", write);
    printf("Cache hits: %lld\n", hit);
    printf("Cache misses: %lld\n", miss);
    return 0;
}
