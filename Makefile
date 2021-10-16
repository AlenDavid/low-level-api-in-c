CC=gcc
CFLAGS=-I.

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

main: main.o
	$(CC) -o main main.o

.PHONY: clean

clean:
	rm -f *.o main