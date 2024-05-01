CC = gcc
CFLAGS = -Wall 

all: main

main: main.o display.o auxiliary.o exchange.o networkInitialization.o exchangeInitialization.o outcome.o
	$(CC) $(LDFLAGS) -o main main.o display.o auxiliary.o exchange.o networkInitialization.o exchangeInitialization.o outcome.o
	
main.o: main.c display.h
	$(CC) $(LDFLAGS) -c main.c

display.o: display.c display.h
	$(CC) $(LDFLAGS) -c display.c

exchange.o: exchange.c exchange.h
	$(CC) $(LDFLAGS) -c exchange.c

auxiliary.o: auxiliary.c auxiliary.h
	$(CC) $(LDFLAGS) -c auxiliary.c

networkInitialization.o: networkInitialization.c networkInitialization.h
	$(CC) $(LDFLAGS) -c networkInitialization.c

exchangeInitialization.o: exchangeInitialization.c exchangeInitialization.h
	$(CC) $(LDFLAGS) -c exchangeInitialization.c

outcome.o: outcome.c outcome.h
	$(CC) $(LDFLAGS) -c outcome.c

clean:
	rm -f main main.o display.o auxiliary.o exchange.o networkInitialization.o exchangeInitialization.o outcome.o result*