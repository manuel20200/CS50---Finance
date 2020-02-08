#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

int main(void)
{
    int words = 0;  //number of words into the sentence
    int letters = 0;    //number of letters into the sentence
    int sentences = 0;  //number of sentence
    int indexINT = 0; //Index integer
    string text = get_string("Text: ");

    for (int i = 0; i < strlen(text); i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z')) //check if the value is a valid letter for getting number of letters
        {
            letters++;
            if (text[i - 1] == ' ') //check number of words by cheking the spaces before letters.
            {
               words++;
            }
        }
        if (text[i] == ' ' && (text[i+1] == '"')) //check number of words by cheking the spaces before ".
        {
            words++;
        }
        if (text[i] == '.' || text[i] == '!' || text[i] == '?' )    //check number of sentences by checking points...
        {
            sentences++;
        }
    }
    if (strlen(text) > 0)   //if string has at mininum one letter increase counting of words
    {
        words++;
    }
    float avgletters = (float)letters / (float)words * 100; //average of letters per 100 words L
    float avgwords = (float)sentences / (float)words * 100; //average of sentences per 100 words S

    float index = (0.0588 * avgletters) - (0.296 * avgwords) - 15.8;    //calcule of index index = 0.0588 * L - 0.296 * S - 15.8

    if (index < 0)  //index less than 0, set value 0
    {
        indexINT = 0;
    }
    if (index >= 16)    //index greater than 16, set value 16
    {
        indexINT = 16;
    }
    else    //index between 1 and 16, round to the nearest integer
    {
        int Aux0 = index * 10;  //get decimal part
        int Aux1 = Aux0 % 10;
        if (Aux1 >= 5)  //if decimal is greater than 0.5 round to the next integer
        {
            indexINT = index;
            indexINT++;
        }
        else    //if decimal is lower than 0.5 round to the last integer
        {
            indexINT = index;
        }

    }

    switch (indexINT)   //print index result
    {
        case 1: printf("Grade 1\n");
        break;
        case 2: printf("Grade 2\n");
        break;
        case 3: printf("Grade 3\n");
        break;
        case 4: printf("Grade 4\n");
        break;
        case 5: printf("Grade 5\n");
        break;
        case 6: printf("Grade 6\n");
        break;
        case 7: printf("Grade 7\n");
        break;
        case 8: printf("Grade 8\n");
        break;
        case 9: printf("Grade 9\n");
        break;
        case 10: printf("Grade 10\n");
        break;
        case 11: printf("Grade 11\n");
        break;
        case 12: printf("Grade 12\n");
        break;
        case 13: printf("Grade 13\n");
        break;
        case 14: printf("Grade 14\n");
        break;
        case 15: printf("Grade 15\n");
        break;
        case 16: printf("Grade 16+\n");
        break;
        default: printf("Before Grade 1\n");
        break;

    }
    /*
    printf("Letter (s): %i \n", letters);
    printf("Word (s): %i \n", words);
    printf("Sentence (s): %i \n", sentences);
    printf("AVG= %0.1f %0.1f %0.1f %i \n", avgletters, avgwords, index, indexINT);
    */
}