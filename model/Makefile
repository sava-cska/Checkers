CFLAGS = -I include -std=c++14 -Wall -Wextra

all: model

obj:
	mkdir obj

obj/board_cell.o: include/board_cell.hpp src/board_cell.cpp | obj
	g++ $(CFLAGS) -c src/board_cell.cpp -o obj/board_cell.o

obj/game_state.o: include/game_state.hpp src/game_state.cpp | obj
	g++ $(CFLAGS) -c src/game_state.cpp -o obj/game_state.o

obj/game.o: include/game.hpp src/game.cpp | obj
	g++ $(CFLAGS) -c src/game.cpp -o obj/game.o

obj/main.o: include/game.hpp src/main.cpp | obj
	g++ $(CFLAGS) -c src/main.cpp -o obj/main.o

model: obj/board_cell.o obj/game_state.o obj/game.o obj/main.o
	g++ $(CFLAGS) obj/board_cell.o obj/game_state.o obj/game.o obj/main.o -lexpat -o model

obj/test_board_cell.o: include/test_board_cell.hpp include/board_cell.hpp test_model/test_board_cell.cpp | obj
	g++ $(CFLAGS) -c test_model/test_board_cell.cpp -o obj/test_board_cell.o

obj/test_game_state.o: include/test_game_state.hpp include/game_state.hpp test_model/test_game_state.cpp | obj
	g++ $(CFLAGS) -c test_model/test_game_state.cpp -o obj/test_game_state.o

obj/test_game.o: include/test_game.hpp include/game.hpp test_model/test_game.cpp | obj
	g++ $(CFLAGS) -c test_model/test_game.cpp -o obj/test_game.o

obj/test.o: include/test_board_cell.hpp include/test_game_state.hpp include/test_game.hpp test_model/test.cpp
	g++ $(CFLAGS) -c test_model/test.cpp -o obj/test.o

test: obj/test_board_cell.o obj/test_game_state.o obj/test_game.o obj/test.o obj/board_cell.o obj/game_state.o obj/game.o
	g++ $(CFLAGS) obj/test_board_cell.o obj/test_game_state.o obj/test_game.o obj/test.o obj/board_cell.o obj/game_state.o obj/game.o -lcppunit -lexpat -o test

clean:
	rm -rf obj test model

.PHONY: all clean
