all: test

test: catch.o hexdump.o test.cpp
	- mkdir -p output
	- g++ -g -o test catch.o test.cpp hexdump.o

catch.o: catch.cpp catch.hpp
	g++ -g -o catch.o -c catch.cpp

hexdump.o: hexdump.c hexdump.h
	gcc -g -o hexdump.o -c hexdump.c

clean:
	rm -rf hexdump.o test output

tidy:
	rm -rf *.o test output