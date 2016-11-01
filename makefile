.PHONY: clean ALL distclean
WORDDIR=.
VPATH=./src

CC=gcc
CPPFLAGS=-I$(WORDDIR)/inc/ -Wall -g
LIBFLAG=-L$(HOME)/lib

BIN=test1

all:$(BIN)

test1:main.o make_log.o
	$(CC) $^ -o $@

%.o:%.c
	$(CC) -c $< -o $@ $(CPPFLAGS) $(FLAGS)


clean:
	-rm -rf *.o $(BIN)
