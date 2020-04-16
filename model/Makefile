CFLAGS = -std=c++14 -Wall -Wextra

all: model

game_state.o: game_state.hpp game_state.cpp
	g++ $(CFLAGS) -c game_state.cpp -o game_state.o

game.o: game.hpp game_state.hpp game.cpp
	g++ $(CFLAGS) -c game.cpp -o game.o

main.o: game.hpp main.cpp
	g++ $(CFLAGS) -c main.cpp -o main.o

model: game.o game_state.o main.o
	g++ $(CFLAGS) game.o game_state.o main.o -lexpat -o model

clean:
	rm game.o game_state.o model main.o

.PHONY: all clean
