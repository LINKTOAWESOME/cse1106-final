CC=gcc
CFLAGS=-Wall -Wextra -std=c11

all: tracker

tracker: src/main.c
	$(CC) $(CFLAGS) -o tracker src/main.c

pi: src/main.c
	$(CC) $(CFLAGS) -DUSE_PIGPIO -o tracker src/main.c -lpigpio -lrt -lpthread

clean:
	rm -f tracker
