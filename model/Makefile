CFLAGS = -I include -std=c++14 -Wall -Wextra

all: model

obj:
	mkdir obj

obj/BoardCell.o: include/BoardCell.hpp src/BoardCell.cpp | obj
	g++ $(CFLAGS) -c src/BoardCell.cpp -o obj/BoardCell.o

obj/GameState.o: include/GameState.hpp src/GameState.cpp | obj
	g++ $(CFLAGS) -c src/GameState.cpp -o obj/GameState.o

obj/Game.o: include/Game.hpp src/Game.cpp | obj
	g++ $(CFLAGS) -c src/Game.cpp -o obj/Game.o

obj/CompPlayer.o: include/CompPlayer.hpp src/CompPlayer.cpp | obj
	g++ $(CFLAGS) -c src/CompPlayer.cpp -o obj/CompPlayer.o

obj/main.o: include/Game.hpp include/CompPlayer.hpp src/main.cpp | obj
	g++ $(CFLAGS) -c src/main.cpp -o obj/main.o

model: obj/BoardCell.o obj/GameState.o obj/Game.o obj/CompPlayer.o obj/main.o
	g++ $(CFLAGS) obj/BoardCell.o obj/GameState.o obj/Game.o obj/CompPlayer.o obj/main.o -lexpat -o model

obj/TestBoardCell.o: include/TestBoardCell.hpp include/BoardCell.hpp test_model/TestBoardCell.cpp | obj
	g++ $(CFLAGS) -c test_model/TestBoardCell.cpp -o obj/TestBoardCell.o

obj/TestGameState.o: include/TestGameState.hpp include/GameState.hpp test_model/TestGameState.cpp | obj
	g++ $(CFLAGS) -c test_model/TestGameState.cpp -o obj/TestGameState.o

obj/TestGame.o: include/TestGame.hpp include/Game.hpp test_model/TestGame.cpp | obj
	g++ $(CFLAGS) -c test_model/TestGame.cpp -o obj/TestGame.o

obj/Test.o: include/TestBoardCell.hpp include/TestGameState.hpp include/TestGame.hpp test_model/Test.cpp
	g++ $(CFLAGS) -c test_model/Test.cpp -o obj/Test.o

test: obj/TestBoardCell.o obj/TestGameState.o obj/TestGame.o obj/Test.o obj/BoardCell.o obj/GameState.o obj/Game.o
	g++ $(CFLAGS) obj/TestBoardCell.o obj/TestGameState.o obj/TestGame.o obj/Test.o obj/BoardCell.o obj/GameState.o obj/Game.o -lcppunit -lexpat -o test

clean:
	rm -rf obj test model

.PHONY: all clean
