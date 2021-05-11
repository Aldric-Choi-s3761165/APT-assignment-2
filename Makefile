.default: all

all: run

clean:
	rm -rf run *.o *.dSYM

run: Tile.o Node.o LinkedList.o Player.o Board.o GameEngine.o Menu.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^