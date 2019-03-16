#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>



int n_treasure(int currentPlayer, struct gameState * state,
               int hand) {
   int drawnTreasure = 0;
   int cardDrawn = 0;
   int maxSearch;
   int * search;
   if (hand) {
      search = state->hand[currentPlayer];
      maxSearch = state->handCount[currentPlayer];
   }
   else {
      search = state->discard[currentPlayer];
      maxSearch = state->discardCount[currentPlayer];
   }
   for (int i = 0; i < maxSearch; i++) {
      cardDrawn = state->hand[currentPlayer][i];
      if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
         drawnTreasure++;
   }
   return drawnTreasure;
}
int main() {
   // Seed random
   srand((unsigned) time(NULL));
   int seed = 1000;
   int numPlayers = 4;
   int any_error = 0;
   int k[10] = {minion, mine, adventurer, great_hall,
      cutpurse, sea_hag, tribute, smithy, council_room, copper};
   int n_cards;      // N cards before adventurer
   int n_discard;    // Discard pile size before
   int treasureHand; // Treasurers before hand
   int treasureDiscard; // Treasure in discard
   int currentPlayer; // Player being used as a turn
   int handSize;      // Hand size to be used
   int deckSize;      // Deck size to be used
   printf("Testing Adventure card\n");
   

   for (int loopN = 0; loopN < 100000; loopN++) {
      any_error=0;
      seed = (rand() % 10000) + 1000;
      struct gameState G;
      initializeGame(numPlayers, k, seed, &G);
      currentPlayer = rand() % numPlayers;     // Max players
      G.whoseTurn = currentPlayer;
      
      // Check to make sure you draw only two additional cards

      deckSize = rand() % (50 + 1);
      handSize = rand() % (deckSize + 1);
      G.deckCount[currentPlayer] = deckSize - handSize;
      G.handCount[currentPlayer] = handSize;
      // Need to ensure that the count is >= 2
      G.supplyCount[copper] += 2;      
      
      treasureHand = n_treasure(currentPlayer, &G, 1);
      n_cards = G.handCount[currentPlayer];
      n_discard = G.discardCount[currentPlayer];
      
      // Play the actual card
      cardEffect(adventurer, 0, 0, 0, &G, 0, NULL);

      // Ensure that the player actually draws 2 cards
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
      if (treasureHand + 2 != n_treasure(currentPlayer, &G, 1)) {
         printf("You failed to draw 2 treasure cards.\n");
         any_error++;
      }
      
      if (any_error) {
         printf("Failed with seed %d, player %d, decksize %d, and handsize %d\n", seed, currentPlayer, deckSize, handSize);
      }
      
 

   }


   if (any_error) {
      printf("There were issues with adventurer_turn()!\n");
   }
   else {
      printf("No errors found with adventurer_turn().\n");
   }
   return 0;
}
