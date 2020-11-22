CFLAGS = -g
OPTFLAGS = -O3

all: timelife

timelife.o:	life.h timelife.c
	$(CC) -c $(CFLAGS) $(OPTFLAGS)  timelife.c
life.o:	life.h life.c
	$(CC) -c $(CFLAGS)  $(OPTFLAGS) life.c

timelife:	timelife.o life.o
	$(CC) -o timelife $(CFLAGS) timelife.o life.o

clean:
	rm -f timelife timelife.o life.o

run:	timelife 
	time ./timelife
