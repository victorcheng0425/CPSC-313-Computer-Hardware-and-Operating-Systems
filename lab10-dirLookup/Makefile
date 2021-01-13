all: test

test: catch.o dirLookup.o test.cpp
	g++ -g -o test catch.o test.cpp dirLookup.o

catch.o: catch.cpp catch.hpp
	g++ -g -o catch.o -c catch.cpp

dirLookup.o: dirLookup.c dirLookup.h
	gcc -g -o dirLookup.o -c dirLookup.c

clean:
	rm -rf dirLookup.o test

tidy:
	rm -rf *.o test