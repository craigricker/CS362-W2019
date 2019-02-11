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
   
   int  return_code;
   int seed = 1000;
   int numPlayers = 4;
   struct gameState G, oldG;
   int any_error = 0;
   int k[10] = {minion, mine, adventurer, great_hall,
      cutpurse, sea_hag, tribute, smithy, council_room, copper};
   printf("Testing Remodel card\n");
   initializeGame(numPlayers, k, seed, &G);
   int num_gardens = 0;
   int num_remodel = 0;
   int num_embargo = 0;
   
   // Set the cards, 0 for remodel, and then others be sea_hag
   // for all players
   for (int i = 0; i < numPlayers; i++) {
      G.hand[i][0] = remodel;
      for (int j = 1; j < G.handCount[i]; j++) {
         G.hand[i][j] = gardens;
      }
   }
   
   // Copy game state for comparisons
   memcpy(&oldG, &G, sizeof(struct gameState));

   
   // Test getting too expensive card
   // To test, get province
   return_code =cardEffect(remodel, province, 1, -1, &G, 0, NULL);

   // player, state, handPos, cohice1, choice 2
   if (return_code != -1) {
      any_error++;
      printf("Incorrectly able to select card that costs too much\n");
   }
   

   // Reset game state
   memcpy(&G, &oldG, sizeof(struct gameState));
   // Test getting a card that should work
   return_code =cardEffect(remodel, province, 1, -1, &G, 0, NULL);

   if (return_code != 0) {
      any_error++;
      printf("Unsuccessfully able to get a card\n");
   }
   

   
   
   for (int currentPlayer = 0; currentPlayer < numPlayers;
        currentPlayer++) {
      initializeGame(numPlayers, k, seed, &G);
      G.whoseTurn = currentPlayer;
      cardEffect(remodel, province, 1, -1, &G, 0, NULL);
      num_gardens = 0;
      num_remodel = 0;
      num_embargo = 0;
      for (int i = 0; i < G.handCount[0]; i++) {
         if (G.hand[0][i] == gardens) {
            num_gardens++;
         }
         else if(G.hand[0][i] == remodel) {
            num_remodel++;
         }
         else if(G.hand[0][i] == embargo) {
            num_embargo++;
         }
      }
      if (num_gardens > 2) {
         printf("Did not correctly discard\n");
         any_error++;
      }
      if (num_remodel >= 0) {
         printf("Did not lose garden card\n");
         any_error++;
      }
      if (num_embargo != 1) {
         printf("Did not gain embargo\n");
         any_error++;
      }
      if (any_error)
         break;
   }

   
 
   
   if (any_error) {
      printf("There were issues with remodel_turn()!\n");
   }
   else {
      printf("No errors found with remodel_turn().\n");
   }
   return 0;
}
