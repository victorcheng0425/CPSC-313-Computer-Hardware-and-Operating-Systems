#Makefile for Hangman
#HANGMAN(6)                   BSD Reference Manual                   HANGMAN(6)
#
#NAME
#     hangman - Computer version of the game hangman
#
#SYNOPSIS
#     hangman
#
#DESCRIPTION
#     In hangman, the computer picks a word from the on-line word list and 
#     you must try to guess it.  The computer keeps track of which letters 
#     have been guessed and how many wrong guesses you have made on the screen 
#     in a graphic fashion.
#
#FILES
#     /usr/share/dict/words	On-line word list
#     or
#     /usr/dict/words		On-line word list
#
#AUTHOR
#     Ken Arnold
#
#
#BSDI BSD/OS                      May 31, 1993                                1

CC=	gcc
CFLAGS=	-g -w
PROG=   hangman
BKUP=	backup-
SRCS=   endgame.c  extern.c getguess.c getword.c main.c \
	playgame.c prdata.c prman.c    prword.c  setup.c
OBJS=	$(SRCS:.c=.o)
LIBS=	-lncurses	# may need termcap

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $*.c

backup:
	tar -cvf $(BKUP)$(PROG).tar Makefile *.c *.h
	gzip $(BKUP)$(PROG).tar

clean:
	rm -rf $(PROG) $(OBJS) *~ *.bak *.gz

# End of Makefile for Hangman



