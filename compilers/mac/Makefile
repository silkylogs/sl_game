# Makefile intended to be executed in a Macintosh system
# Start the build process from the project root directory with
# `make -f compilers/mac/Makefile`

INCLUDEDIR = include
LIBDIR = lib/mac/
SOURCEDIR = src
BUILDIR = build
BUILDFLAGS := -Wall -std=c++98
LINKFLAGS := -lSDL2

all:
	g++	-o $(BUILDIR)/game \
		-I$(INCLUDEDIR) \
		-L$(LIBDIR) \
		$(SOURCEDIR)/*.cpp \
		$(SOURCEDIR)/*.c \
		$(BUILDFLAGS) \
		$(LINKFLAGS)

clean:
	rm -r build/*
