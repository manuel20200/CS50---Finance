#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    string plaintext = " ";
    char number = '5';
    int integer = number;
    int key, keymod, plaintext_size = 0;
    int keyreal = 0;
    int cypher_aux = 0;
    int matrix[10]; //values ascii 0 = 48, 1 = 49, ..., 9 = 57
    if (argc == 2)  //two arguments valid in the command argument
    {

        for (int i = 0, n = 48; i < 10; i++)
        {
            matrix[i] = n;
            n++;
        }
        int size = strlen(argv[1]); //size of the key, how many digits has the key
        int numero[size];
        for (int i = 0; i < size; i++)  //convert every chart of the command line to an integer
        {
            for (int j = 0; j < 10; j++)
            {
                if (matrix[j] == argv[1][i])
                {
                    numero[i] = j;
                }
            }
            if (argv[1][i] < '0' || argv[1][i] > '9') //check if CLA is not a valid value, if yes print a error message
            {
                printf("Usage: ./caesar key \n");
                return 1;
            }
        }
        for (int i = 0; i < size; i++)  //take every integer of the past lines and get one integer
        {
            key = key + (numero[size - 1 - i] * pow (10, i));
        }
        keymod = key % 26;
        plaintext = get_string("Plaintext: ");
        plaintext_size = strlen(plaintext);
        char ciphertext[plaintext_size];
        for (int i = 0; i <= plaintext_size; i++)    //clear char array
        {
            ciphertext[i] = 0;
        }
        for (int i = 0; i < plaintext_size; i++)    //Check every character of input plaintext
        {
            if ((plaintext[i] >= 'A' && plaintext[i] <= 'Z') || (plaintext[i] >= 'a' && plaintext[i] <= 'z'))
            {
                cypher_aux = plaintext[i] + keymod;
                ciphertext[i] = cypher_aux;
                //printf("%i %i %i %i \n", plaintext[i], ciphertext[i], keymod, cypher_aux);
            }
            else
            {
                ciphertext[i] = plaintext[i];
            }
            if (plaintext[i] >= 'a' && plaintext[i] <= 'z')   //check uppercase letters
            {
                if (cypher_aux > 122)
                {
                    keyreal = cypher_aux - 122;
                    ciphertext[i] = 96 + keyreal;   //a = 97    Start from first letter
                    //printf("%c %i %i \n", ciphertext[i], keymod, keyreal);
                }
            }
            if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')   //check lowercase letters
            {
                if (ciphertext[i] > 90)
                {
                    keyreal = ciphertext[i] - 90;
                    ciphertext[i] = 64 + keyreal;   //A = 65    Start from first letter
                }
            }

        }



        printf("Ciphertext: %s\n", ciphertext);
        //printf("%i %i %i %i \n", key, size, numero[0], numero[1]);
        return 0;
    }
    else    //if there are more than two arguments
    {
        printf("Digit a correct value\n");
        return 1;
    }
}

/*int stringtoint(string x)
{
    int size = strlen(x);
    for (int i = 0; i < size; i++)
    {
        i--;
    }
    return 1;
}*/