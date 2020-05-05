// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 17576;

// Hash table  check two first letters 26x26
node *table[N];

// Number of words in the dictionary
unsigned int sizeW = 0;

int g = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int res = 0;
    int equ = 0;
    int found = 0;
    char wordT[50];
    char dicw[50];
    int dim = strlen(word);
    int dimD = 0;
    node *point = NULL;

    //clean register for text words
    for (int i = 0; i < 50; i++)
    {
        wordT[i] = '\000';
    }

    //printf("word: %s \n", word);

    //convert all word characters in lowercases
    for (int i = 0; word[i] != '\000'; i++)
    {
        wordT[i] = tolower(word[i]);
    }

    //get pos array in table[N]
    res = hash(wordT);

    //check all the linked list
    if (table[res] != NULL)
    {
        for (point = table[res]; point != NULL; point = point->next)
        {
            //clean register for dictionary words
            for (int i = 0; i < 50; i++)
            {
                dicw[i] = '\000';
            }

            //length of dictionary word
            dimD = strlen(point->word);

            //convert all point characters in lowercases
            for (int i = 0; i < dimD; i++)
            {
                dicw[i] = tolower(point->word[i]);
            }

            /*
            if (word[0] == 'a' && dim == 1)
            {
                printf("word: %c %i %c \n", word[0], (int)word[1], word[2]);
                printf("wordT: %c %i %i \n", wordT[0], (int)wordT[1], (int)wordT[2]);
                printf("dicw: %c %i %i \n", dicw[0], (int)dicw[1], (int)dicw[2]);
                printf("point->word: %c %i %i %c \n", point->word[0], (int)point->word[1], (int)point->word[2], point->word[2]);
            }
            */

            //found = strcmp (dicw, wordT); doesnt work, check why

            //compare function between dictionary and file words
            equ = 0;
            for (int i = 0; i < dim; i++)
            {
                if (dicw[i] == wordT[i])
                {
                    equ++;
                }
            }

            //compare word size
            if (dim == equ && dim == dimD)
            {
                found = 99;
            }
            else
            {
                found = 33;
            }

            //printf("\n%i\n", found);

            //return true if found word into dictionary
            if (found == 99)
            {
                return true;
            }


        }
    }

    return false;

}

// Hashes word to a number
unsigned int hash(const char *wordh)
{
    char word[50];
    int dir = 0;
    int z = 0;
    z = strlen(wordh);
    g++;

    for (int i = 0; i < 50; i++)
    {
        word[i] = '\000';
    }

    for (int i = 0; wordh[i] != '\000'; i++)
    {
        word[i] = wordh[i];
    }

    /*
    if (word[0] == 'a' && z < 5 && g < 10){
        printf("9-hash: %c %c %c %i \n", word[0], word[1], word[2], z);}*/


    //check first word letter
    if (word[0] >= 65 && word[0] <= 90)
    {
        dir = (word[0] - 65) * 676;
    }

    if (word[0] >= 97 && word[0] <= 122)
    {
        dir = (word[0] - 97) * 676;
    }

    //check second word letter
    if (word[1] >= 65 && word[1] <= 90 && z >= 2)
    {
        dir = dir + (word[1] - 65) * 26;
    }

    if (word[1] >= 97 && word[1] <= 122 && z >= 2)
    {
        dir = dir + (word[1] - 97) * 26;
    }

    //check third word letter
    if (word[2] >= 65 && word[2] <= 90 && z >= 3)
    {
        dir = dir + (word[2] - 65);
    }

    if (word[2] >= 97 && word[2] <= 122 && z >= 3)
    {
        dir = dir + (word[2] - 97);
    }

    // return where save/look for word
    return dir;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    int dirL = 0;
    int a = 0;
    char wordD[50];
    //node *tmp = NULL;

    //set all table pointers to NULL
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    //open file dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("It cannot open dictionary");
        return false;
    }

    // a != EOF;
    while (a != EOF)
    {
        /*
        int where = ftell(file);
        if (where < 20){
            printf("1-puntero: %i \n", where);}
        */

        a = fscanf(file, "%s", wordD);

        /*
        if (where < 20){
            printf("1- word: %s %i \n", wordD, a);}
        */

        if (a == EOF)
        {
            break;
        }

        //Count number of words load from the dictionary
        sizeW++;

        dirL = hash(wordD);

        /*
        if (where < 20){
        printf("2-hash: %i \n", dirL);}
        */

        //allocate memory for every dictionary word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("It cannot load dictionary word into memory");
            return false;
        }

        /*
        if (where < 20){
        printf("3-malloc: %p \n", n);}
        */

        if (table[dirL] == NULL)
        {
            table[dirL] = n;
            strcpy(n->word, wordD);
            n->next = NULL;
        }
        else
        {
            n->next = table[dirL];
            table[dirL] = n;
            strcpy(n->word, wordD);
        }

        /*
        if (dirL == 0){
        printf("4-word: %s \n", n->word);
        printf("4-next: %p \n", n->next);
        printf("4-table[dirL]: %p \n", table[dirL]);}
        */
    }

    fclose(file);
    // TODO
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (sizeW != 0)
    {
        //printf("%i \n", sizeW);
        return sizeW;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *temp = NULL;
    for (int i = 0; i < N; i++)
    {
        for (node *point = table[i]; point != NULL; point = temp)
        {
            temp = point->next;
            free(point);
        }
    }


    // TODO
    return true;
}
