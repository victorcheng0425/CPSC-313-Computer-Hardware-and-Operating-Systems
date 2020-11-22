all: hello
O ?= -O0

%.o: %.c $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

hello: hello.o
	$(CC) $(CFLAGS) $(O) -o $@ $^ -lm

clean:
	rm -f hello *.o
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all clean
