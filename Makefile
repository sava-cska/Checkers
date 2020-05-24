CXX = g++
CXXFLAGS = -std=c++17 -O2 -pedantic -Wall -Wextra -Werror
LDFLAGS = -lexpat -lsfml-network -lsfml-system -lsfml-window -lsfml-graphics -lpthread -lcppunit
INC = -Inetwork -Imodel -Iui -Icontroller -Iai -Iserver

OBJDIR = obj
MAIN = main
MAIN_TEST_MODEL = main_test_model
MAIN_SERVER = main_server

EXE = game
TEST = test
SERVER = run_server

SRCDIR_MODEL = model
SRCDIR_NETWORK = network
SRCDIR_UI = ui
SRCDIR_CONTROLLER = controller
SRCDIR_AI = ai
SRCDIR_SERVER = server
SRCDIR_TEST_MODEL = test_model

OBJECTS_MODEL = $(patsubst $(SRCDIR_MODEL)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR_MODEL)/*.cpp))
OBJECTS_NETWORK = $(patsubst $(SRCDIR_NETWORK)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR_NETWORK)/*.cpp))
OBJECTS_UI = $(patsubst $(SRCDIR_UI)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR_UI)/*.cpp))
OBJECTS_CONTROLLER = $(patsubst $(SRCDIR_CONTROLLER)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR_CONTROLLER)/*.cpp))
OBJECTS_AI = $(patsubst $(SRCDIR_AI)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR_AI)/*.cpp))
OBJECTS_SERVER = $(patsubst $(SRCDIR_SERVER)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR_SERVER)/*.cpp))
OBJECTS_TEST_MODEL = $(patsubst $(SRCDIR_TEST_MODEL)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR_TEST_MODEL)/*.cpp))

all: $(EXE)

$(EXE): model network ui controller ai $(MAIN)
	$(CXX) $(OBJECTS_MODEL) $(OBJECTS_NETWORK) $(OBJECTS_UI) $(OBJECTS_CONTROLLER) $(OBJECTS_AI) $(OBJDIR)/$(MAIN).o -o $(EXE) $(LDFLAGS)

$(TEST): model test_model $(MAIN_TEST_MODEL)
	$(CXX) $(OBJECTS_MODEL) $(OBJECTS_TEST_MODEL) $(OBJDIR)/$(MAIN_TEST_MODEL).o -o $(TEST) $(LDFLAGS)

$(SERVER): model network controller ai server $(MAIN_SERVER)
	$(CXX) $(OBJECTS_MODEL) $(OBJECTS_NETWORK) $(OBJECTS_CONTROLLER) $(OBJECTS_AI) $(OBJECTS_SERVER) $(OBJDIR)/$(MAIN_SERVER).o -o $(SERVER) $(LDFLAGS)

model: $(OBJDIR) $(OBJECTS_MODEL)

network: $(OBJDIR) $(OBJECTS_NETWORK)

ui: $(OBJDIR) $(OBJECTS_UI)

controller: $(OBJDIR) $(OBJECTS_CONTROLLER)

ai: $(OBJDIR) $(OBJECTS_AI)

server: $(OBJDIR) $(OBJECTS_SERVER)

test_model: $(OBJDIR) $(OBJECTS_TEST_MODEL)

$(MAIN): $(OBJDIR) $(OBJDIR)/$(MAIN).o

$(MAIN_SERVER): $(OBJDIR) $(OBJDIR)/$(MAIN_SERVER).o

$(MAIN_TEST_MODEL): $(OBJDIR) $(OBJDIR)/$(MAIN_TEST_MODEL).o

$(OBJDIR)/%.o: $(SRCDIR_MODEL)/%.cpp $(SRCDIR_MODEL)/%.hpp
	$(CXX) $(CXXFLAGS) $(INC) -c -MMD -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR_NETWORK)/%.cpp $(SRCDIR_NETWORK)/%.hpp
	$(CXX) $(CXXFLAGS) $(INC) -c -MMD -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR_UI)/%.cpp $(SRCDIR_UI)/%.hpp
	$(CXX) $(CXXFLAGS) $(INC) -c -MMD -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR_CONTROLLER)/%.cpp $(SRCDIR_CONTROLLER)/%.hpp
	$(CXX) $(CXXFLAGS) $(INC) -c -MMD -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR_AI)/%.cpp $(SRCDIR_AI)/%.hpp
	$(CXX) $(CXXFLAGS) $(INC) -c -MMD -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR_SERVER)/%.cpp $(SRCDIR_SERVER)/%.hpp
	$(CXX) $(CXXFLAGS) $(INC) -c -MMD -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR_TEST_MODEL)/%.cpp $(SRCDIR_TEST_MODEL)/%.hpp
	$(CXX) $(CXXFLAGS) $(INC) -c -MMD -o $@ $<

$(OBJDIR)/$(MAIN).o: $(MAIN).cpp
	$(CXX) $(CXXFLAGS) $(INC) -c -MMD -o $@ $<

$(OBJDIR)/$(MAIN_SERVER).o: $(MAIN_SERVER).cpp
	$(CXX) $(CXXFLAGS) $(INC) -c -MMD -o $@ $<

$(OBJDIR)/$(MAIN_TEST_MODEL).o: $(MAIN_TEST_MODEL).cpp
	$(CXX) $(CXXFLAGS) $(INC) -c -MMD -o $@ $<

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(EXE) $(TEST) $(SERVER)

.PHONY: all clean model network ui ai test_model server $(MAIN) $(MAIN_TEST_MODEL) $(MAIN_SERVER)
