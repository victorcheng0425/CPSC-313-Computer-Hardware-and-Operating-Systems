all: test

test: catch.o copy.o test.cpp
	g++ -g -o test catch.o test.cpp copy.o

catch.o: catch.cpp catch.hpp
	g++ -g -o catch.o -c catch.cpp

copy.o: copy.c copy.h
	gcc -g -o copy.o -c copy.c

clean:
	rm -rf copy.o test

tidy:
	rm -rf *.o test