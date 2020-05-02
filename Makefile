CXX = g++
CXXFLAGS = -std=c++17 -O2 -pedantic -Wall -Wextra
LDFLAGS = -lexpat -lsfml-network -lsfml-system -lsfml-window -lsfml-graphics -lpthread
INC = -Inetwork -Imodel -Iui -Icontroller

OBJDIR = obj
MAIN = main

SRCDIR_MODEL = model
SRCDIR_NETWORK = network
SRCDIR_UI = ui
SRCDIR_CONTROLLER = controller

OBJECTS_MODEL = $(patsubst $(SRCDIR_MODEL)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR_MODEL)/*.cpp))
OBJECTS_NETWORK = $(patsubst $(SRCDIR_NETWORK)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR_NETWORK)/*.cpp))
OBJECTS_UI = $(patsubst $(SRCDIR_UI)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR_UI)/*.cpp))
OBJECTS_CONTROLLER = $(patsubst $(SRCDIR_CONTROLLER)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR_CONTROLLER)/*.cpp))

EXE = game

all: $(EXE)

$(EXE): model network ui controller $(MAIN)
	$(CXX) $(OBJECTS_MODEL) $(OBJECTS_NETWORK) $(OBJECTS_UI) $(OBJECTS_CONTROLLER) $(OBJDIR)/$(MAIN).o -o $(EXE) $(LDFLAGS)

model: $(OBJDIR) $(OBJECTS_MODEL)

network: $(OBJDIR) $(OBJECTS_NETWORK)

ui: $(OBJDIR) $(OBJECTS_UI)

controller: $(OBJDIR) $(OBJECTS_CONTROLLER)

$(MAIN): $(OBJDIR) $(OBJDIR)/$(MAIN).o

$(OBJDIR)/%.o: $(SRCDIR_MODEL)/%.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c -MMD -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR_NETWORK)/%.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c -MMD -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR_UI)/%.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c -MMD -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR_CONTROLLER)/%.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c -MMD -o $@ $<

$(OBJDIR)/$(MAIN).o: $(MAIN).cpp
	$(CXX) $(CXXFLAGS) $(INC) -c -MMD -o $@ $<

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(EXE) $(TEST)

.PHONY: all clean model network ui $(MAIN)
