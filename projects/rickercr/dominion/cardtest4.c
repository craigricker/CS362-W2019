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


   int seed = 1000;
   int numPlayers = 2;
   struct gameState G;
   int any_error = 0;
   int k[10] = {minion, mine, adventurer, great_hall,
      cutpurse, sea_hag, tribute, smithy, council_room, copper};
   printf("Testing Council Room card\n");
   
   
   
   
   
   
   for (int currentPlayer = 0; currentPlayer < numPlayers;
        currentPlayer++) {
      initializeGame(numPlayers, k, seed, &G);
      G.whoseTurn = currentPlayer;

  
      
      // Store number of cards before hand
      int num_cards = G.handCount[currentPlayer];
      int num_buys = G.numBuys;
      int num_cards_p2 = G.handCount[1];
      int num_discard = G.discardCount[currentPlayer];
      
      cardEffect(council_room, -1, 1, -1, &G, 0, NULL);
      
      // Check if cards successfully drawn
      if (num_cards + 4 - 1 != G.handCount[currentPlayer]) {
         printf("You did now draw the correct number of cards\n");
         any_error++;
      }
      
      // Check if card successfully discarded
      if (num_discard + 1 != G.discardCount[currentPlayer]) {
         printf("You did not discard cards properly\n");
         any_error++;
      }
      
      // Check if the other player gained a card
      if (num_cards_p2 + 1 != G.handCount[1]) {
         printf("Other players did not draw a card\n");
         any_error++;
      }
      
      
      // Check if buys increased
      if (num_buys + 1 != G.numBuys) {
         printf("Number of buys is not correct\n");
         any_error++;
      }
      
      if (any_error)
         break;
   }


   
   

   if (any_error) {
      printf("There were issues with council_room_turn()!\n");
   }
   else {
      printf("No errors found with council_room_turn().\n");
   }
   return 0;
}
