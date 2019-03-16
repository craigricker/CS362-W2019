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
   int seed = 1000;
   int numPlayers = 4;
   struct gameState G, oldG;
   int any_error = 0;
   int k[10] = {minion, mine, adventurer, great_hall,
      cutpurse, sea_hag, tribute, smithy, council_room, copper};
   printf("Testing Smithy card\n");
   initializeGame(numPlayers, k, seed, &G);
   // Copy game state for comparisons
   memcpy(&oldG, &G, sizeof(struct gameState));

   

   // Check to make sure you draw only two additional cards
   int n_cards;
   int n_discard;
   int deckSize;
   int handSize;
   int currentPlayer;
   for (int i = 0; i < 5; i++) {
      initializeGame(numPlayers, k, seed, &G);
      currentPlayer = rand() % numPlayers;     // Max players
      G.whoseTurn = currentPlayer;
      
      
      deckSize = rand() % (50 + 1);
      handSize = rand() % (deckSize + 1);
      G.deckCount[currentPlayer] = deckSize - handSize;
      G.handCount[currentPlayer] = handSize;
      n_cards = G.handCount[currentPlayer];
      n_discard = G.discardCount[currentPlayer];
      
      
//         smithy_turn(i, &G, 0);
      cardEffect(smithy, 0, 0, 0, &G, 0, NULL);
      if (n_discard + 1 != G.discardCount[i] &&
          n_cards + 3 != G.handCount[i]) {
         printf("Discard and hand count incorrect.\n");
         any_error++;
      }
      else if(n_discard + 1 != G.discardCount[i]){
         printf("Discard count incorrect.\n");
         any_error++;
      }
      else if (n_cards + 3 != G.handCount[i]) {
         printf("Hand count incorrect\n");
         any_error++;
      }
   }
   
   
   if (any_error) {
      printf("There were issues with smithy_turn()!\n");
   }
   else {
      printf("No errors found with smithy_turn().\n");
   }
   return 0;
}
