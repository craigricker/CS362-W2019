#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main() {
   int k[10] = {adventurer, council_room, feast, gardens,
      mine, remodel, smithy, village, baron, great_hall};
   struct gameState G;
   int any_error = 0;
   int return_val;
   int start_player = initializeGame(4, k, 3, &G);
   printf("Testing \"whoseTurn()\":\n");
   
   return_val = whoseTurn(&G);
   
   
   // Testing to ensure the player number
   // is correct immediatly after game init
   if (return_val != start_player) {
      printf("Game incorrectly reporting start player after initialization\n");
      any_error++;
   }
   
   playCard(-1, -1, -1, -1, &G);
   
   if (return_val != start_player + 1) {
      printf("Game incorrectly reporting player after a single turn\n");
      any_error++;
   }
   
   if (any_error)
      printf("Errors found in whoseTurn()\n");
   else
      printf("No errors found with whoseTurn().\n");
   
   
   
   
   return 0;
   
}
