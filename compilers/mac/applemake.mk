# Makefile intended to be executed in a Macintosh system
# Start the build process from the project root directory with
# `make -f compilers/mac/applemake.mk`

CC := cc
INCLUDEDIR = include
LIBDIR = lib/mac/
SOURCEDIR = src
BUILDIR = build
BUILDFLAGS := -Wall -std=c99
LINKFLAGS := -lSDL2

all:
	$(CC)	-o $(BUILDIR)/game \
		-I$(INCLUDEDIR) \
		-L$(LIBDIR) \
		$(SOURCEDIR)/*.c \
		$(BUILDFLAGS) \
		$(LINKFLAGS)

clean:
	rm -r build/*
