CC = gcc
CFLAGS = -Wall 

all: main

main: main.o display.o networkInitialization.o
	$(CC) $(LDFLAGS) -o main main.o display.o networkInitialization.o
main.o: main.c display.h
	$(CC) $(LDFLAGS) -c main.c

display.o: display.c display.h
	$(CC) $(LDFLAGS) -c display.c

networkInitialization.o: networkInitialization.c networkInitialization.h
	$(CC) $(LDFLAGS) -c networkInitialization.c


clean:
	rm -f main main.o display.o networkInitialization.o