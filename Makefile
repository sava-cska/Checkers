CXX = g++
CXXFLAGS = -std=c++17 -O2 -pedantic -Wall -Wextra -Werror
LDFLAGS = -lsfml-network -lsfml-system -lpthread
INC = -Inetwork/include -Imodel/include

SRCDIR_MODEL = model/src
SRCDIR_NETWORK = network/src
OBJDIR = obj
MAIN = main

OBJECTS_MODEL = $(patsubst $(SRCDIR_MODEL)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR_MODEL)/*.cpp))
OBJECTS_NETWORK = $(patsubst $(SRCDIR_NETWORK)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR_NETWORK)/*.cpp))

$(info $(OBJECTS_MODEL))

EXE = game

all: $(EXE)

$(EXE): model network $(MAIN)
	$(CXX) $(OBJECTS_MODEL) $(OBJDIR)/$(MAIN).o $(OBJECTS_NETWORK) -o $(EXE) $(LDFLAGS)

model: $(OBJDIR) $(OBJECTS_MODEL)

network: $(OBJDIR) $(OBJECTS_NETWORK)

$(MAIN): $(OBJDIR) $(OBJDIR)/$(MAIN).o

$(OBJDIR)/%.o: $(SRCDIR_MODEL)/%.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c -MMD -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR_NETWORK)/%.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c -MMD -o $@ $<

$(OBJDIR)/$(MAIN).o: $(MAIN).cpp
	$(CXX) $(CXXFLAGS) $(INC) -c -MMD -o $@ $<

$(OBJDIR):
	mkdir -p $(OBJDIR)

#	g++ $(CXXFLAGS) expat-2.2.9/lib/xmlparse.o expat-2.2.9/lib/xmlrole.o expat-2.2.9/lib/xmltok.o obj/model.o obj/main.o -o model

clean:
	rm -rf $(OBJDIR) $(EXE) $(TEST)

.PHONY: all clean model network $(MAIN)
