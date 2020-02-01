#include<stdio.h>
#include<cs50.h>

int main(void)
{
    long cardnumber = get_long("Number: ");
   
    long number = cardnumber;
    int i = 0;
    int checksum = 0;   
    int size = 0;   //number of digits in the card number
    int c1, c2 = 0; //c1 first digit   c2 second digit   from left to right
    
    while (number > 0)  //from number we'll get every digit, retiring every digit from number until we get only one digit
    {
        int digit = number % 10;    //get every digit
        number = number / 10;   //when we get digit we retire the digit from number
        size++;

        if (number < 10 && number > 0)  //get the second digit  left to right
        { 
            c2 = digit;
        }
        if (number == 0)    //get the first digit  left to right
        {
            c1 = digit;
        }
    
        if (i == 0) //add digit that musnt be multiply by 2
        {
            i = 1;
            checksum = checksum + digit;
        }
        else    //add digit that must be multiply by 2
        {
            i = 0;
            if (2 * digit >= 10) //if result of multiplication by 2 is two digits, add the two digits to checksum
            {
                int digit1 = (2 * digit) % 10;
                checksum = checksum + digit1 + 1;
            }
            else    //if result of multiplication by 2 is one digit, add to checksum
            {
                checksum = (2 * digit) + checksum; 
            }
        }
            
        //printf("Digit : %i %li %i %i %i %i\n",digit,number,c1,c2,checksum, size);  //only for testing 
    }

    //VISA          SIZE: 13 to 16      FIRST NUMBERS: 4
    //AMEX          SIZE: 15            FIRST NUMBERS: 34 or 37
    //MASTERCARD    SIZE: 16            FIRST NUMBERS: 51 to 55

    if (size >= 13 && size <= 16 && c1 == 4 && (checksum % 10 == 0))    //check VISA
    {
        printf("VISA\n");
    }
    else if (size == 15 && c1 == 3 && (c2 == 4 || c2 == 7) && (checksum % 10 == 0)) //check AMEX
    {
        printf("AMEX\n");
    }
    else if (size == 16 && c1 == 5 && (c2 == 1 || c2 == 2 || c2 == 3 || c2 == 4 || c2 == 5) && (checksum % 10 == 0))
    { 
        printf("MASTERCARD\n");
    }
    else 
    {
        printf("INVALID\n");
    }
}
