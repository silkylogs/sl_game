# Makefile intended to be executed in a Macintosh system
# to create a windows executable
# Start the build process from the project root directory with
# `make -f compilers/mac/winmake.mk`

COMPILER := /opt/homebrew/Cellar/mingw-w64/10.0.0_4/bin/x86_64-w64-mingw32-gcc
INCLUDEDIR = include
LIBDIR = lib/win32/
SOURCEDIR = src
BUILDIR = build
BUILDFLAGS := -Wall -std=c99
LINKFLAGS := -mwindows -lmingw32 -lSDL2main -lSDL2

all:
	$(COMPILER)	-o $(BUILDIR)/game \
			-I$(INCLUDEDIR) \
			-L$(LIBDIR) \
			$(SOURCEDIR)/*.c \
			$(BUILDFLAGS) \
			$(LINKFLAGS)

clean:
	rm -r build/*

