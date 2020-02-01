#include <cs50.h>
#include <stdio.h>



int main(void)
{
    int Height; //Declare integer tag for height
    
    //////////// Require and check Height between 1 and 9/////////
    do
    {
    Height = get_int("Height: ");    
    } 
    while (Height <= 0 || Height > 8);
    //////////////////////////////////////////////////
        
     for (int i = 0; i < Height; i++)  ///// loop for the levels of pyramid
     {
         for (int j = 0; j < (Height-i-1); j++)   //// loop for spaces of the left side
         {
          printf (" "); 
         } 
                  
         for (int k = 0; k <= i; k++)   /// loop for left side of the pyramid (blocks)
         {
          printf ("#"); 
         } 
         
          printf ("  ");  ////// central spaces
         
           for (int l = 0; l <= i; l++)   ///// loop for right side of the pyramid (blocks)
         {
          printf ("#");   
         }
         
          printf ("\n");  /// final jump   
      }    
    
}
