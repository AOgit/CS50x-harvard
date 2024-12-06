#include <cs50.h>
#include <stdio.h>

int coins (int denomination);

int change_owed;
int main (void)
{
   int coins_number=0;
   // Prompt the user for the Change owed
   do
   {
      change_owed = get_int("Change owed: ");
   }
   while(change_owed < 0);

   // Сalculate the number of coins of each denomination from the largest to the smallest
   coins_number += coins(25);
   coins_number += coins(10);
   coins_number += coins(5);
   coins_number += coins(1);

   printf("%i\n", coins_number);
}

int coins (int denomination)
{
   int coins_number = change_owed / denomination;
   if ( coins_number > 0)
   {
      change_owed = change_owed - (coins_number*denomination);
   }
   return coins_number;
}
