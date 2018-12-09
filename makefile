CC=g++
CFLAGS=-I -lncurses

make: main.cpp
	g++ -o main main.cpp -I. -lncurses
clean:
	rm -f *.o *.exe
