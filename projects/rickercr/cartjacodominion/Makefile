CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe


randomtestadventurer: playdom randomtestadventurer.c
	gcc dominion.o rngs.o randomtestadventurer.c -o randomtestadventurer $(CFLAGS)

randomtestsmithy: playdom randomtestsmithy.c
	gcc dominion.o rngs.o randomtestsmithy.c -o randomtestsmithy $(CFLAGS)

unittestadventurer: playdom unittestadventurer.c
	gcc dominion.o rngs.o unittestadventurer.c -o unittestadventurer $(CFLAGS)


unittestsmithy: playdom unittestsmithy.c
	gcc dominion.o rngs.o unittestsmithy.c -o unittestsmithy $(CFLAGS)

assignment5Test: all randomtestadventurer randomtestsmithy unittestadventurer unittestsmithy
	./randomtestadventurer >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	./randomtestsmithy> randomtestsmithy.out
	gcov -b dominion.c >> randomtestsmithy.out
	./unittestadventurer> unittestadventurer.out
	gcov -b dominion.c >> unittestadventurer.out
	./unittestsmithy >> unittestsmithy.out
	gcov -b dominion.c >> unittestsmithy.out
