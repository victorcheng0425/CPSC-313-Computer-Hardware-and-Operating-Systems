PROGRAMS = w01 w02 w03 w01block
INCLUDES = -I.

CFLAGS = -g -O3 -Wall $(INCLUDES)

all: $(PROGRAMS)

%.o:%.c
	$(CC) $(CFLAGS) -c $<

w01: w01.o
	$(CC) $(CFLAGS) -o $@ w01.o

w01block: w01block.o
	$(CC) $(CFLAGS) -o $@ w01block.o

w02: w02.o
	$(CC) $(CFLAGS) -o $@ w02.o

w02block: w02block.o
	$(CC) $(CFLAGS) -o $@ w02block.o

w03: w03.o
	$(CC) $(CFLAGS) -o $@ w03.o

w03block: w03block.o
	$(CC) $(CFLAGS) -o $@ w03block.o

clean:
	rm -f $(PROGRAMS) *.o core a.out data
