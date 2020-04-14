all: ./bin/main.o | ./bin
	g++ ./bin/main.o -o Chess -lsfml-graphics -lsfml-window -lsfml-system

./bin/main.o: ./src/main.cpp | ./bin
	g++ -c ./src/main.cpp -o ./bin/main.o

./bin:
	mkdir ./bin