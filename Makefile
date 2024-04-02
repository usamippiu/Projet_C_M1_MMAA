CC=g++
LD=g++
CFLAGS=-g -Wall -pedantic -std=c++11 -Werror
LIBS=-lm

all: main

main: main.o image.o pixel.o
	$(LD) main.o image.o pixel.o $(LIBS) -o main

main.o: main.cpp
	$(CC) -c $(CFLAGS) main.cpp -o main.o

pixel.o: pixel.cpp pixel.h
	$(CC) -c $(CFLAGS) pixel.cpp -o pixel.o

image.o: image.cpp image.h
	$(CC) -c $(CFLAGS) image.cpp -o image.o

clean:
	rm -f main main.o pixel.o image.o

fullclean: clean
	rm -f *~ *.fig.bak

