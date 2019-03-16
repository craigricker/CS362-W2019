#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>


int n_treasure(int currentPlayer, struct gameState * state ) {
   int drawnTreasure = 0;
   int cardDrawn = 0;
   for (int i = 0; i < state->handCount[currentPlayer]; i++) {
      if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
         drawnTreasure++;
   }
   return drawnTreasure;
}
int main() {
   int seed = 1000;
   int numPlayers = 4;
   struct gameState G;
   int any_error = 0;
   int k[10] = {minion, mine, adventurer, great_hall,
      cutpurse, sea_hag, tribute, smithy, council_room, copper};
   printf("Testing Adventure card\n");
   

   for (int currentPlayer = 0; currentPlayer < numPlayers;
        currentPlayer++) {
      initializeGame(numPlayers, k, seed, &G);
      G.whoseTurn = currentPlayer;
      // Check to make sure you draw only two additional cards
      int n_cards = G.handCount[currentPlayer];
      int n_discard = G.discardCount[currentPlayer];
      int treasure = n_treasure(currentPlayer, &G);
      cardEffect(adventurer, 0, 0, 0, &G, 0, NULL);
      if (n_cards + 2 != G.handCount[currentPlayer]) {
         printf("Did not successfully draw 2 cards\n");
         any_error++;
      }
      // Check to ensure the discard pile is larger, or same size
      if (n_discard < G.discardCount[currentPlayer]) {
         printf("Did not successfully discard all cards\n");
         any_error++;
      }
      
      // Check to ensure you actually increase treasure by 2
      if (treasure + 2 != n_treasure(currentPlayer, &G)) {
         printf("You failed to draw 2 treasure cards.\n");
         any_error++;
      }
      if (any_error)
         break;
   }


   if (any_error) {
      printf("There were issues with adventurer_turn()!\n");
   }
   else {
      printf("No errors found with adventurer_turn().\n");
   }
   return 0;
}
