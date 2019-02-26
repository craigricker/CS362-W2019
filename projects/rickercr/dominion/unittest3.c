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
   int player = 0;
   int any_error = 0;
   int return_val;
   initializeGame(4, k, 3, &G);
   printf("Testing \"shuffle()\":\n");
   
   printf("Testing shuffle return condition after init\n");
   return_val = shuffle(player, &G);
   
   
   // Testing when shuffled with full deck, return is 0
   if (return_val != 0) {
      printf("Shuffle incorrectly returning failure after initialization\n");
      any_error++;
   }
   
   int * old_hand;
   int n_shuffles = 1000;
   int n_same;
   int same_order = 0;
   // Make an array same size as hand of player
   old_hand = malloc(sizeof(int) * G.deckCount[player]);
   printf("Testing returns new order for all players\n");
   for (int i = 0; i < n_shuffles; i++) {
      // Copy old hand into new, shuffle, check if identical
      memcpy(old_hand, G.deck[player],
             sizeof(int) * G.deckCount[player]);
      shuffle(player, &G);
      n_same = 0;
      for (int i = 0; i < G.deckCount[player]; i++) {
         if (old_hand[i] == G.deck[player][i])
            n_same++;
      }
      
      // Check to see if they are in the exact same manner
      if (n_same == G.deckCount[player]) {
         same_order++;
      }
   }
   
   // Card order should be different more than
   // 50% of the time!
   if (same_order > n_shuffles/2) {
      printf("Identical shuffle order occured 50%%\n");
      any_error++;
   }
   
   // Set the number of cards in a player's hand
   // to zero, and it should no longer succeeed
   G.deckCount[player] = 0;
   printf("Checking deck with 1 card isn't shuffled\n");
   if (shuffle(player, &G) == 0) {
      printf("Shuffled an empty deck.\n");
      any_error++;
   }
   
   
   if (any_error)
      printf("Errors found in shuffle()\n");
   else
      printf("No errors found with shuffle().\n");
   free(old_hand);
   return 0;
   
}
