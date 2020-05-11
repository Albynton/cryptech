# Start of Makefile

CC = gcc

FLAGS = `pkg-config --cflags --libs gtk+-3.0` -rdynamic

.PHONY: clean

cryptech: main.c caesar.h polyalph.h vigenere.h
	$(CC) -o $@ main.c $(FLAGS)

clean:
	rm -f cryptech
