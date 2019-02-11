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

unittest1: all unittest1.c
	gcc -o unittest1 unittest1.c dominion.o rngs.o -g $(CFLAGS)

unittest2: all unittest2.c
	gcc -o unittest2 unittest2.c dominion.o rngs.o -g $(CFLAGS)

unittest3: all unittest3.c
	gcc -o unittest3 unittest3.c dominion.o rngs.o -g $(CFLAGS)

unittest4: all unittest4.c
	gcc -o unittest4 unittest4.c dominion.o rngs.o -g $(CFLAGS)

cardtest1: all cardtest1.c
	gcc -o cardtest1 cardtest1.c dominion.o rngs.o -g $(CFLAGS)

cardtest2: all cardtest2.c
	gcc -o cardtest2 cardtest2.c dominion.o rngs.o -g $(CFLAGS)

cardtest3: all cardtest3.c
	gcc -o cardtest3 cardtest3.c dominion.o rngs.o -g $(CFLAGS)

cardtest4: all cardtest4.c
	gcc -o cardtest4 cardtest4.c dominion.o rngs.o -g $(CFLAGS)


unittestresults: clean unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	# This creates a blank file, even if it exists
	> unittestresult.out
	# Loop through, and output information for all tests
	# Dirty trick to safe typing
	for number in 1 2 3 4 ; do \
		./unittest$$number >> unittestresult.out ; \
		gcov -b dominion.c >> unittestresult.out ; \
		cat dominion.c.gcov >> unittestresult.out ; \
		./cardtest$$number >> unittestresult.out ; \
		gcov -b  dominion.c >> unittestresult.out ; \
		cat dominion.c.gcov >> unittestresult.out ; \
	done
	

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
