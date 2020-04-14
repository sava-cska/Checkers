CFLAGS= -g -I ./include

all: ./bin/main.o ./bin/draw_smf.o | ./bin
	g++ $(CFLAGS) ./bin/main.o  ./bin/draw_smf.o  -o Chess -lsfml-graphics -lsfml-window -lsfml-system

./bin/main.o: ./src/main.cpp | ./bin
	g++ $(CFLAGS) -c ./src/main.cpp -o ./bin/main.o

./bin/draw_smf.o: ./src/draw_smf.cpp | ./bin 
	g++ $(CFLAGS) -c ./src/draw_smf.cpp -o ./bin/draw_smf.o

./bin:
	mkdir ./bin