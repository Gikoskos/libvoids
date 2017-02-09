CC = gcc
CPP = -I./../
LINKER = -L./../ -lGiDS
CFLAGS = -Wall -ggdb -std=c99

SRCS = $(wildcard *.c)
EXES = $(patsubst %.c,%.exe,$(SRCS))

.PHONY: clean all

all: $(EXES)

%.exe: %.c
	$(CC) $(CFLAGS) $(CPP) $^ -o $@ $(LINKER)

clean:
	@echo off
	@del *.o *.exe
	@echo on
