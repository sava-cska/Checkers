CXX = g++
CXXFLAGS = -std=c++17 -O2 -pedantic -Wall -Wextra -Werror
LDFLAGS = -lexpat -lsfml-network -lsfml-system -lsfml-window -lsfml-graphics -lpthread -lcppunit
INC = -Inetwork -Imodel -Iui -Icontroller -Iai

OBJDIR = obj
MAIN = main_text
MAIN_TEST_MODEL = main_test_model

SRCDIR_MODEL = model
SRCDIR_NETWORK = network
SRCDIR_UI = ui
SRCDIR_CONTROLLER = controller
SRCDIR_AI = ai
SRCDIR_TEST_MODEL = test_model

OBJECTS_MODEL = $(patsubst $(SRCDIR_MODEL)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR_MODEL)/*.cpp))
OBJECTS_NETWORK = $(patsubst $(SRCDIR_NETWORK)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR_NETWORK)/*.cpp))
OBJECTS_UI = $(patsubst $(SRCDIR_UI)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR_UI)/*.cpp))
OBJECTS_CONTROLLER = $(patsubst $(SRCDIR_CONTROLLER)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR_CONTROLLER)/*.cpp))
OBJECTS_AI = $(patsubst $(SRCDIR_AI)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR_AI)/*.cpp))
OBJECTS_TEST_MODEL = $(patsubst $(SRCDIR_TEST_MODEL)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR_TEST_MODEL)/*.cpp))

EXE = game
TEST = test

all: $(EXE)

$(EXE): model network ui controller ai $(MAIN)
	$(CXX) $(OBJECTS_MODEL) $(OBJECTS_NETWORK) $(OBJECTS_UI) $(OBJECTS_CONTROLLER) $(OBJECTS_AI) $(OBJDIR)/$(MAIN).o -o $(EXE) $(LDFLAGS)

$(TEST): $(MAIN_TEST_MODEL) model test_model
	$(CXX) $(OBJECTS_MODEL) $(OBJECTS_TEST_MODEL) $(OBJDIR)/$(MAIN_TEST_MODEL).o -o $(TEST) $(LDFLAGS)

model: $(OBJDIR) $(OBJECTS_MODEL)

network: $(OBJDIR) $(OBJECTS_NETWORK)

ui: $(OBJDIR) $(OBJECTS_UI)

controller: $(OBJDIR) $(OBJECTS_CONTROLLER)

ai: $(OBJDIR) $(OBJECTS_AI)

test_model: $(OBJDIR) $(OBJECTS_TEST_MODEL)

$(MAIN): $(OBJDIR) $(OBJDIR)/$(MAIN).o

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

$(OBJDIR)/%.o: $(SRCDIR_TEST_MODEL)/%.cpp $(SRCDIR_TEST_MODEL)/%.hpp
	$(CXX) $(CXXFLAGS) $(INC) -c -MMD -o $@ $<

$(OBJDIR)/$(MAIN).o: $(MAIN).cpp
	$(CXX) $(CXXFLAGS) $(INC) -c -MMD -o $@ $<

$(OBJDIR)/$(MAIN_TEST_MODEL).o: $(MAIN_TEST_MODEL).cpp
	$(CXX) $(CXXFLAGS) $(INC) -c -MMD -o $@ $<

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(EXE) $(TEST)

.PHONY: all clean model network ui ai test_model $(MAIN) $(MAIN_TEST_MODEL)
