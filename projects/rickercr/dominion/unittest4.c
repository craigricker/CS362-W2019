#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>



int * generate_int_array(int n) {
   int * new_array = malloc(n * sizeof(int));
   for (int i = 0; i < n; i++)
      new_array[i] = rand();
   
   return new_array;
}
int main() {
   int k[10] = {adventurer, council_room, feast, gardens,
      mine, remodel, smithy, village, baron, great_hall};
   struct gameState G;
   int any_error = 0;
   initializeGame(4, k, 3, &G);
   // Seed random
   srand(time(NULL));
   printf("Testing \"kingdomCards()\":\n");
   

   
   int * old, * new_hand;
   int n_checks = 1000;

   printf("Checking kingdomCards() creates array in proper order\n");
   // Make an array same size as hand of player
   for (int i = 0; i < n_checks; i++) {
      // Generate random integer array of isze 10
      old = generate_int_array(10);
      new_hand = kingdomCards(old[0], old[1], old[2],
                              old[3], old[4], old[5],
                              old[6], old[7], old[8],
                              old[9]);
      for (int i = 0; i < 10; i++) {
         if (old[i] != new_hand[i])
            any_error++;
      }
      
      if (any_error > 0) {
         printf("kingdomCards did not create correct order\n");
      }
      
      // Free memory
      free(old);
      free(new_hand);
   }
   
   if (any_error)
      printf("Errors found in kingdomCards()\n");
   else
      printf("No errors found with kingdomCards().\n");
   
   return 0;
   
}
