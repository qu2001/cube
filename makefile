SRC=$(wildcard *.c)
start: $(SRC)
	gcc -g -Wall $(SRC) -o $@ `sdl-config --libs --cflags`
static:
	gcc -static -Wall -ansi -O2 -march=native $(SRC) -o cube `sdl-config --static-libs --cflags`
