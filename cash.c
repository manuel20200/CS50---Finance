#include <stdio.h>
#include <cs50.h>
#include <math.h>

float change = 0;
int changeI, quarters, dimes, nickels, pennies = 0; //coins number for every value

int main(void)
{
    while (change <= 0) //get permited value
    {
        change = get_float("Change Owe: ");
    }

    changeI = round(change * 100);    //convert Float to Int

    if (changeI >= 25)  //get number of quarters
    {  
        quarters = changeI / 25;
        changeI = changeI - (quarters * 25);
        //printf ("%i %i \n",quarters,changeI);
    }
    if (changeI >= 10) //get number of dimes
    {
        dimes = changeI / 10;
        changeI = changeI - (dimes * 10);
        //printf ("%i %i \n",dimes,changeI);
    }
    if (changeI >= 5)   //get number of nickels
    {
        nickels = changeI / 5;
        changeI = changeI - (nickels * 5);
        //printf ("%i %i \n",nickels,changeI);
    }
    if (changeI < 5) //get number of pennies
    {
        pennies = changeI;
        //printf ("%i %i \n",pennies,changeI);
    }
    printf("Coins= %i \n", (quarters + dimes + nickels + pennies)); 
    
}
