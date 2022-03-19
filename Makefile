CC = g++
CPPFLAGS = -std=c++11
DEBUGFLAGS = -g -Wall
INCLUDE = include
SRCDIR = src
BINDIR = bin
OBJDIR = obj
TESTDIR = test
LIB = -lSDL2 -lSDL2_image -lSDL2_ttf

SRC = $(wildcard $(SRCDIR)/*.cpp)
BIN = $(wildcard $(BINDIR)/*)
TESTSRC = $(filter-out $(SRCDIR)/main.cpp, $(SRC)) 
OBJ = $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
TESTOBJ = $(TESTSRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

main: $(OBJ) | $(BINDIR)
	$(CC) $(CPPFLAGS) $(LIB) $^ -o $(BINDIR)/$@

debug: $(OBJ) | $(BINDIR)
	$(CC) $(DEBUGFLAGS) $(CPPFLAGS) $(LIB) $^ -o $(BINDIR)/$@

$(OBJDIR)/test%.o: $(TESTDIR)/test%.cpp | $(OBJDIR)
	$(CC) $(CPPFLAGS) -c $< -I$(INCLUDE) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(DEBUGFLAGS) $(CPPFLAGS) -c $< -I$(INCLUDE) -o $@

$(OBJDIR): 
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

test%: $(OBJDIR)/test%.o $(TESTOBJ) 
	$(CC) $(CPPFLAGS) $^ -o $(BINDIR)/$@

clean:
	rm -rf $(OBJDIR)/*.o $(BINDIR)/*
