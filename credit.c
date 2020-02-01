#include<stdio.h>
#include<cs50.h>

int main (void)
{
    long cardnumber = get_long("Number: ");
   
    long number = cardnumber;
    int i = 0;
    int checksum = 0;   
    int size = 0;   //number of digits in the card number
    int c1,c2 = 0;  //c1 first digit   c2 second digit   from left to right
    
    while (number > 0)
    {
        int digit = number % 10;
        number = number / 10;
        size++;

        if (number < 10 && number > 0)
        { 
            c2 = digit;
        }
        if (number == 0)
        {
             c1 = digit;
        }
    
        if ( i == 0 )
        {
            i = 1;
            checksum = checksum + digit;
        }
        else
        {
            i = 0;
            if (2*digit >= 10)
            {
                int digit1 = (2*digit)%10;
                checksum = checksum+digit1+1;
            }
            else 
            {
                checksum = (2*digit)+checksum;
            }
        }
            
        //printf("Digit : %i %li %i %i %i %i\n",digit,number,c1,c2,checksum, size);  //only for testing 
    }

    if (size >= 13 && size <= 16 && c1 == 4 && (checksum % 10 == 0))
    {
        printf("VISA\n");
    }
    else if (size == 15 && c1 == 3 && (c2 == 4 || c2 == 7) && (checksum % 10 == 0))
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
