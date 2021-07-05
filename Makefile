# Makefile for LiveData program
# Author: rtlogik
#
# Targets:
# livdata (goal)
# lifo.o
# 

CC=gcc
OBJS=lifo.o livedata.o

main: $(OBJS) osiris.h
	gcc -o main $(OBJS)

lifo.o: lifo.h osiris.h
livedata.o: livedata.h osiris.h

.PHONY: clean
clean:
	rm -f *.o
