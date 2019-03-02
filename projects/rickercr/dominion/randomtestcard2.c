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
   srand((unsigned) time(NULL));
   int  return_code;
   int seed = 1000;
   int numPlayers = 4;
   int requestedCard;
   int foundN, num_remodel;
   struct gameState G;
   int any_error = 0;
   int k[10] = {minion, mine, adventurer, great_hall,
      cutpurse, sea_hag, tribute, smithy, council_room, copper};
   printf("Testing Remodel card\n");

   
   for (int runN = 0; runN < 100000; runN++) {
      initializeGame(numPlayers, k, seed, &G);
      requestedCard = rand() %28;
      G.whoseTurn = rand() % numPlayers; ;
      cardEffect(remodel, requestedCard, 1, -1, &G, 0, NULL);
      foundN = 0;
      num_remodel = 0;
      for (int i = 0; i < G.handCount[0]; i++) {
         if(G.hand[0][i] == remodel) {
            num_remodel++;
         }
         else if(G.hand[0][i] == requestedCard) {
            foundN++;
         }
      }

      
      if (num_remodel >= 0) {
         printf("Did not lose remodel card\n");
         any_error++;
      }
      if (foundN >= 1) {
         printf("Did not gain correct card\n");
         any_error++;
      }
   }


   
 
   
   if (any_error) {
      printf("There were issues with remodel_turn()!\n");
   }
   else {
      printf("No errors found with remodel_turn().\n");
   }
   return 0;
}
