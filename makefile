# Start of Makefile

CC = gcc

FLAGS = `pkg-config --cflags --libs gtk+-3.0` -rdynamic

.PHONY: clean

cryptech: main.c crypt1.h crypt2.h crypt3.h
	$(CC) -o $@ main.c $(FLAGS)
exe: cryptech
	./cryptech

clean:
	rm -f cryptech
