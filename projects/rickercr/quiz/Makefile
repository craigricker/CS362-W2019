CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c
	gcc -o testme testme.c   $(CFLAGS) 



run: testme
	chmod +x testme 
	./testme

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.so *.out testme 
