CFLAGS = -I include -Wall -Wextra -std=c++14

all: model

obj:
	mkdir obj

obj/model.o: include/model.h src/model.cpp | obj
	g++ $(CFLAGS) -c src/model.cpp -o obj/model.o

obj/main.o: main.cpp | obj
	g++ $(CFLAGS) -c main.cpp -o obj/main.o

model: obj/model.o obj/main.o
	g++ $(CFLAGS) expat-2.2.9/lib/xmlparse.o expat-2.2.9/lib/xmlrole.o expat-2.2.9/lib/xmltok.o obj/model.o obj/main.o -o model

clean:
	rm -rf obj model

.PHONY: all clean
