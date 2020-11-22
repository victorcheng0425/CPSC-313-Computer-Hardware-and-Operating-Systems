
PROGRAMS = ecology ecology2 stride_struct mm-ijk mm-ikj mm-jik mm-jki mm-kij mm-kji
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

mm-ikj: mm-ikj.o
	$(CC) $(CFLAGS) -o mm-ikj $< -lm

mm-jik: mm-jik.o
	$(CC) $(CFLAGS) -o mm-jik $< -lm

mm-jki: mm-jki.o
	$(CC) $(CFLAGS) -o mm-jki $< -lm

mm-kij: mm-kij.o
	$(CC) $(CFLAGS) -o mm-kij $< -lm

mm-kji: mm-kji.o
	$(CC) $(CFLAGS) -o mm-kji $< -lm

clean:
	rm -f $(PROGRAMS) *.o core a.out data
