CXX = g++
CXXFLAGS = -std=c++17 -O2 -pedantic -Wall -Wextra -Werror -Iinclude
LDFLAGS = -lsfml-network -lsfml-system

SRCDIR = src
OBJDIR = obj

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))

SERVER_EXE = run_server
SERVER_SRCDIR = src/server
SERVER_OBJECTS = $(patsubst $(SERVER_SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SERVER_SRCDIR)/*.cpp))

CLIENT_EXE = run_client
CLIENT_SRCDIR = src/client
CLIENT_OBJECTS = $(patsubst $(CLIENT_SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(CLIENT_SRCDIR)/*.cpp))

all: client server

client: $(CLIENT_EXE)

server: $(SERVER_EXE)

$(CLIENT_EXE): $(OBJDIR) $(OBJECTS) $(CLIENT_OBJECTS)
	$(CXX) $(OBJECTS) $(CLIENT_OBJECTS) -o $(CLIENT_EXE) $(LDFLAGS)

$(SERVER_EXE): $(OBJDIR) $(OBJECTS) $(SERVER_OBJECTS)
	$(CXX) $(OBJECTS) $(SERVER_OBJECTS) -o $(SERVER_EXE) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

$(OBJDIR)/%.o: $(CLIENT_SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

$(OBJDIR)/%.o: $(SERVER_SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(SERVER_EXE) $(CLIENT_EXE) $(TEST)

.PHONY: clean all