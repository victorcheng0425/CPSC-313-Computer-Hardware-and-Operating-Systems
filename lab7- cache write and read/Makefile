CFLAGS = -g -Wall -Wno-unused-function

all: test

test: catch.o cache-ref.o cache.o test.cpp
	g++ $(CFLAGS) -o test catch.o cache-ref.o cache.o test.cpp

catch.o: catch.cpp catch.hpp
	g++ $(CFLAGS) -o catch.o -c catch.cpp

cache.o: cache.h cache.c
	gcc $(CFLAGS) -o cache.o -c cache.c

clean:
	rm -f test cache.o
tidy:
	rm -f test cache.o catch.o