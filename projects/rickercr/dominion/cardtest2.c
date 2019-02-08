#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>


int main() {
   
   
   /*
    States to test/check:
    Return is 0
    Full deck
    empty deck
    */
   
   int n_treas, n_drawn;
   
   int temp[MAX_HAND];
   int seed = 1000;
   int numPlayers = 2;
   struct gameState G, oldG;
   int any_error = 0;
   int k[10] = {minion, mine, adventurer, great_hall,
      cutpurse, sea_hag, tribute, smithy, council_room, copper};
   printf("Testing Smithy card\n");
   initializeGame(numPlayers, k, seed, &G);
   // Copy game state for comparisons
   memcpy(&oldG, &G, sizeof(struct gameState));
   int currentPlayer = 0;
   

   // Check to make sure you draw only two additional cards
   int n_cards;
   int n_discard;
   for (int i = 0; i < numPlayers; i++) {
      for (int j = 0; j < seed; j++) {
         // Reset game state
         memcpy(&G, &oldG, sizeof(struct gameState));
         n_cards = G.handCount[i];
         n_discard = G.discardCount[i];
         smithy_turn(i, &G, 0);
         if (n_discard + 1 != G.discardCount[i] &&
             n_cards + 3 != G.handCount[i]) {
            printf("Discard and hand count incorrect.\n");
            any_error++;
            break;
         }
         else if(n_discard + 1 != G.discardCount[i]){
            printf("Discard count incorrect.\n");
            any_error++;
            break;
         }
         else if (n_cards + 3 != G.handCount[i]) {
            printf("Hand count incorrect\n");
            any_error++;
            break;
         }
      }
      if (any_error)
         break;
   }
   
   if (any_error) {
      printf("There were issues with smithy_turn()!\n");
   }
   else {
      printf("No errors found with smithy_turn().\n");
   }
   return 0;
}
