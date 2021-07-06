# Makefile for LiveData program
# Author: rtlogik
#

CC = gcc
OBJECTS = main.o lifo.o livedata.o
CPPFLAGS = -I ./include

vpath %.h ./include
vpath %.c ./src

main: $(OBJECTS)
	gcc  -Wall $(OBJECTS) -o main;
	make clean;
	echo "Success!"

main.o: datastructs.h
lifo.o: lifo.h 
livedata.o: livedata.h 

.PHONY: clean
clean:
	rm -f *.o
