CXX = g++
CXXFLAGS = -std=c++17 -O2 -pedantic -Wall -Wextra -Werror
LDFLAGS = -lsfml-network -lsfml-system -lsfml-window -lsfml-graphics -lpthread
INC = -Inetwork/include -Imodel/include -Iui/include

OBJDIR = obj
MAIN = main

SRCDIR_MODEL = model/src
SRCDIR_NETWORK = network/src
SRCDIR_UI = ui/src

OBJECTS_MODEL = $(patsubst $(SRCDIR_MODEL)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR_MODEL)/*.cpp))
OBJECTS_NETWORK = $(patsubst $(SRCDIR_NETWORK)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR_NETWORK)/*.cpp))
OBJECTS_UI = $(patsubst $(SRCDIR_UI)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR_UI)/*.cpp))

EXE = game

$(info $(OBJECTS_UI))

all: $(EXE)

$(EXE): model network ui $(MAIN)
	$(CXX) $(OBJECTS_MODEL) $(OBJECTS_NETWORK) $(OBJECTS_UI) $(OBJDIR)/$(MAIN).o -o $(EXE) $(LDFLAGS)
#	g++ $(CXXFLAGS) expat-2.2.9/lib/xmlparse.o expat-2.2.9/lib/xmlrole.o expat-2.2.9/lib/xmltok.o obj/model.o obj/main.o -o model

model: $(OBJDIR) $(OBJECTS_MODEL)

network: $(OBJDIR) $(OBJECTS_NETWORK)

ui: $(OBJDIR) $(OBJECTS_UI)

$(MAIN): $(OBJDIR) $(OBJDIR)/$(MAIN).o

$(OBJDIR)/%.o: $(SRCDIR_MODEL)/%.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c -MMD -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR_NETWORK)/%.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c -MMD -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR_UI)/%.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c -MMD -o $@ $<

$(OBJDIR)/$(MAIN).o: $(MAIN).cpp
	$(CXX) $(CXXFLAGS) $(INC) -c -MMD -o $@ $<

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(EXE) $(TEST)

.PHONY: all clean model network ui $(MAIN)
