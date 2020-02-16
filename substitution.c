#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc == 2)  //check for only one command line argument (CLA)
    {
        string code[3];
        string plaintext = " ";
        string ciphertext = " ";
        code[0] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //UPPERCASE LETTERS
        code[1] = "abcdefghijklmnopqrstuvwxyz"; //lowecase letters
        code[2] = "                          ";
        char caracter[26];  //check for repeated caracteres into the key word
        int aux[5] = {0, 0, 0, 0, 0};
        int validletter = 0;    //check if each caracter in CLA is a valid caracter
        int check = 0;
        int size = 0;
        for (int i = 0, n = strlen(argv[1]); i <= n; i++)   //check every character into the CLA
        {
            if ((argv[1][i] >= 'a' && argv[1][i] <= 'z') || (argv[1][i] >= 'A' && argv[1][i] <= 'Z'))
            {
                validletter++; //every character must be a valid caracter
            }
            for (int j = 0; j < 26; j++) //check for unrepeated caracteres into the CLA
            {
                if ((argv[1][i] == code[0][j]) || (argv[1][i] == code[1][j]))
                {
                    caracter[j] = '1';  //check that all characters are present into the CLA
                }
            }
        }
        size = strlen(argv[1]); //size of CLA
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
        if (size != 26 || validletter != 26 || check != 26) //check for a valid CLA
        {
            printf("Please digit a valid key.\n");
            return 1;
        }
        else
        {
            plaintext = get_string("plaintext: ");
            int k = strlen(plaintext);  //get the plaintext size
            char text[k];   //create tag for ciphertext
            for (int i = 0; i <= k; i++)
            {
                for (int j = 0; j < 26; j++)    //conversion of plaintex to cuphertext
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
                printf("%c",text[i]); //print ciphertext
            }
            printf("\n");
        }
    }
    else //if there is no command argument or more than two print error
    {
        printf("Please digit a valid command.\n");
        return 1;
    }
    return 0;
}


