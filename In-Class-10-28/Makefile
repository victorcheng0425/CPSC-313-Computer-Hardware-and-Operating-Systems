
PROGRAMS = ecology ecology2 stride_struct mm-ijk
INCLUDES = -I.

CFLAGS = -O3 -Wall $(INCLUDES)

all: $(PROGRAMS)


%.s:%.c
	$(CC) -S $(CFLAGS) $<

%.o:%.c
	$(CC) $(CFLAGS) -c $<

ecology2: ecology2.o
	$(CC) $(CFLAGS) -o ecology2 $<

ecology: ecology.o
	$(CC) $(CFLAGS) -o ecology $<

stride_struct: stride_struct.o
	$(CC) $(CFLAGS) -o stride_struct $<

mm-ijk: mm-ijk.o
	$(CC) $(CFLAGS) -o mm-ijk $< -lm

clean:
	rm -f $(PROGRAMS) *.o core a.out data
