all: test

test: catch.o parsePath.o test.cpp
	g++ -g -o test catch.o test.cpp parsePath.o

catch.o: catch.cpp catch.hpp
	g++ -g -o catch.o -c catch.cpp

parsePath.o: parsePath.c parsePath.h
	gcc -g -o parsePath.o -c parsePath.c

clean:
	rm -rf parsePath.o test

tidy:
	rm -rf *.o test