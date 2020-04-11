CFLAGS = -I include -Wall -Wextra -Werror -std=c++14

all: model

obj:
	mkdir obj

obj/model.o: include/model.h src/model.cpp | obj
	g++ $(CFLAGS) -c src/model.cpp -o obj/model.o

model: obj/model.o
	g++ $(CFLAGS) obj/model.o -o model

clean:
	rm -rf obj model

.PHONY: all clean
