#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        string code[3];
        string plaintext = " ";
        string ciphertext = " ";
        code[0] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        code[1] = "abcdefghijklmnopqrstuvwxyz";
        code[2] = "                          ";
        char caracter[26];
        int aux[5] = {0, 0, 0, 0, 0};
        int validletter = 0;
        int check = 0;
        int size = 0;
        check = 0;
        validletter = 0;
        for (int i = 0, n = strlen(argv[1]); i <= n; i++)
        {

            if ((argv[1][i] >= 'a' && argv[1][i] <= 'z') || (argv[1][i] >= 'A' && argv[1][i] <= 'Z'))
            {
                validletter++;
            }
            for (int j = 0; j < 26; j++)
            {
                if ((argv[1][i] == code[0][j]) || (argv[1][i] == code[1][j]))
                {
                    caracter[j] = '1';
                    //printf("%i %c %c\n", j, caracter[0], caracter[5]);
                }
            }
        }
        size = strlen(argv[1]);
        //printf("%s %s %i %i %s \n", plaintext, argv[1], validletter, check, code[2]);
        for (int i = 0; i < 26; i++)
        {

            if (caracter[i] == '1')
            {
                check++;
            }
            else
            {
                check--;
            }
        }


        if (size != 26 || validletter != 26 || check != 26)
        {
            printf("Please digit a valid key.\n");
            return 1;
        }
        else
        {
            plaintext = get_string("plaintext: ");
            int k = strlen(plaintext);
            char text[k];
            for (int i = 0; i <= k; i++)
            {
                for (int j = 0; j < 26; j++)
                {
                    if (plaintext[i] == code[0][j]) //check if plaintext letters are uppercase letters
                    {
                        text[i] = toupper(argv[1][j]);
                        break;
                    }
                    if (plaintext[i] == code[1][j]) //check if plaintext letters are lowercase letters
                    {
                        text[i] = tolower(argv[1][j]);
                        break;
                    }
                    else
                    {
                        text[i] = plaintext[i];
                    }
                }
            }
            printf("ciphertext: ");
            for (int i = 0, n = strlen(plaintext); i < n; i++)
            {
                printf("%c",text[i]);
            }
            printf("\n");
        }
    }
    else
    {
        printf("Please digit a valid command.\n");
        return 1;
    }
    return 0;
}


