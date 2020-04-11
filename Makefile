all: ./bin/main.o
	g++ ./bin/main.o -o Chess -lsfml-graphics -lsfml-window -lsfml-system

./bin/main.o: ./src/main.cpp
	g++ -c ./src/main.cpp -o ./bin/main.o