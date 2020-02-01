#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int Height;   //declare variable for height
    
    do  //loop do-while for require valid height
    {
      Height = get_int("Height: ");    
    } 
    while (Height <= 0 || Height > 8);
    
    for (int i = 0; i < Height; i++)    //loop for levels of pyramid
    {
    for (int k = 0; (k < (Height - i - 1)); k++) 
    {
      printf(" ");
    }   
    for (int j = 0; j <= i; j++)    //loop for quantity of blocks in each level
    {
      printf("#");    
    }
      printf("\n");     
 }
    
}
