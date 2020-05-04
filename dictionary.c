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
    //node *point = NULL;

    //clean register for text words
    for (int i = 0; i < 50; i++)
    {
        wordT[i] = ' ';
    }

    //printf("word: %s \n", word);

    //convert all word characters in lowercases
    for (int i = 0; word[i] != '\000'; i++)
    {
        wordT[i] = tolower(word[i]);
    }

    res = hash(wordT);

    //check all the linked list
    for (node *point = table[res]; point != NULL; point = point->next)
    {
        //clean register for dictionary words
        for (int i = 0; i < 50; i++)
        {
            dicw[i] = ' ';
        }

        //convert all point characters in lowercases
        dimD = strlen(point->word);
        for (int i = 0; i < dimD; i++)
        {
            dicw[i] = tolower(point->word[i]);
        }

        /*
        for (int i = 0; i < 10; i++)
        {
            printf("%c", wordT[i]);
        }
        printf("  ");
        for (int i = 0; i < 10; i++)
        {
            printf("%c", dicw[i]);
        }
        */

        //found = strcmp (dicw, wordT);
        equ = 0;
        for (int i = 0; i < dim; i++)
        {
            if (dicw[i] == wordT[i])
            {
                equ++;
            }
        }

        if (dim == equ && dim == dimD)
        {
            found = 99;
        }
        else
        {
            found = 33;
        }

        //printf("\n%i\n", found);



        if (found == 99)
        {
           return true;
        }


    }

    return false;

}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int dir = 0;

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
    if (word[1] >= 65 && word[1] <= 90)
    {
        dir = dir + (word[1] - 65) * 26;
    }

    if (word[1] >= 97 && word[1] <= 122)
    {
        dir = dir + (word[1] - 97) * 26;
    }

    //check third word letter
    if (word[2] >= 65 && word[2] <= 90)
    {
        dir = dir + (word[2] - 65);
    }

    if (word[2] >= 97 && word[2] <= 122)
    {
        dir = dir + (word[2] - 97);
    }

    // TODO
    return dir;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    int dirL = 0;
    int a = 0;
    char characters_a[26];
    char characters_A[26];
    char wordD[50];
    //node *tmp = NULL;

    //set all table pointers to NULL
    for (int i = 0; i < N; i++)
    {
       table[i] = NULL;
    }

    for (int i = 0; i < 26; i++)
    {
        characters_a[i] = 97 + i;
        characters_A[i] = 65 + i;
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
        a = fscanf(file, "%s", wordD);

        //printf("%s \n", wordD);

        if (a == EOF)
        {
            break;
        }

        //Count number of words load from the dictionary
        sizeW++;

        dirL = hash(wordD);

        //allocate memory for every dictionary word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }



        if (table[dirL] == NULL)
        {
            table[dirL] = n;
            strcpy(n->word, wordD);
        }
        else
        {
            n->next = table[dirL];
            table[dirL] = n;
            strcpy(n->word, wordD);
        }

        /*
        printf("%s \n", n->word);
        printf("%p \n", n->next);
        printf("%p \n", table[dir]);
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
        for (node *point = table[i]; point != NULL; point = temp->next)
        {
            temp = point;
            free(point);
        }
    }


    // TODO
    return true;
}
