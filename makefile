CC=g++
CFLAGS=	-I.

all: game

game: main.o tank.o bullet.o functions.o
	$(CC) $(CFLAGS) tank.o bullet.o functions.o main.o -lncurses -o game

tank.o: tank.cpp tank.h globals.h
	$(CC) $(CFLAGS) -c tank.cpp -lncurses

bullet.o: bullet.cpp bullet.h globals.h
	$(CC) $(CFLAGS) -c bullet.cpp -lncurses

functions.o: functions.cpp functions.h globals.h
	$(CC) $(CFLAGS) -c functions.cpp -lncurses

main.o: main.cpp main.h globals.h
	$(CC) $(CFLAGS) -c main.cpp -lncurses

clean:
	rm -f *.o *.exe
