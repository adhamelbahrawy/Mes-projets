# Compiler settings
CC = gcc -g
CXXFLAGS = -Wall
IFLAGS = -Iinclude

# Makefile settings
APPNAME = main
EXT = .c
SRCDIR = src
OBJDIR = obj
MPATH = bin

SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)

vpath %.h include
####################### Targets beginning here #########################

all: $(APPNAME)

# Builds the app
$(APPNAME): $(OBJ)
	mkdir -p $(MPATH)
	$(CC) $(CXXFLAGS) -o $(MPATH)/$@ $^
	doxygen Doxyfile

# Building rule for .o files and its .c in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	mkdir -p $(OBJDIR)
	$(CC) $(CXXFLAGS) -o $@ -c $< $(IFLAGS) 

# Builds the documentation
doc:
	doxygen Doxyfile

# Cleans complete project
.PHONY: clean
clean:
	rm -fr $(OBJDIR) $(MPATH) doc