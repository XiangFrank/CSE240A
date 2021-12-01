CC=gcc
OPTS=-g -std=c99 -Werror

all: main.o predictor.o gshare.o tournament.o
	$(CC) $(OPTS) -lm -o predictor main.o predictor.o gshare.o tournament.o

main.o: main.c predictor.h
	$(CC) $(OPTS) -c main.c

predictor.o: predictor.h predictor.c gshare.h gshare.c tournament.h tournament.c
	$(CC) $(OPTS) -c predictor.c gshare.c tournament.c

gshare.o: gshare.h gshare.c
	$(CC) $(OPTS) -c gshare.c

tournament.o: tournament.h tournament.c
	$(CC) $(OPTS) -c tournament.c

clean:
	rm -f *.o predictor;
