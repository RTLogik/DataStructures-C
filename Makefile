# Makefile for LiveData program
# Author: rtlogik
#
# Targets:
# livdata (goal)
# lifo.o
# 

CC=gcc
OBJECTS=lifo.o livedata.o

main: $(OBJECTS) osiris.h
	gcc -o main $(OBJECTS)

lifo.o: lifo.h osiris.h
livedata.o: livedata.h osiris.h

.PHONY: clean
clean:
	rm -f *.o
