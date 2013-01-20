WIN_SFML_DIR = C:\Users\Terrance\Documents\SFML-1.6
LIN_SFML_DIR = /home/terrance/SFML-1.6

CC := g++

DEBUG := true
OPTIMIZATIONLEVEL = O3

COMPILEFLAGS := -w
LINKERFLAGS := 

SOURCES := $(wildcard src/*.cpp)

OBJECTS := $(patsubst src/%.cpp,obj/%.o,$(SOURCES))

EXENAME :=
WINDOWSEXENAME := main.exe
LINUXEXENAME := main.lin_exe

INCLUDES :=
WINDOWSINCLUDES := -I "$(WIN_SFML_DIR)\include"
LINUXINCLUDES := -I$(LIN_SFML_DIR)/include

LIBRARIES := 
LINUXLIBRARIES := -lsfml-window -lsfml-system -L $(LIN_SFML_DIR)/lib -lGL -lGLU -static-libgcc -static-libstdc++
WINDOWSLIBRARIES := -lsfml-window-s -lsfml-system-s -L "$(WIN_SFML_DIR)/lib" -lopengl32 -lglu32 -static-libgcc -static-libstdc++

UNAME = $(shell uname)

ifeq ($(UNAME), Linux)
	EXENAME = $(LINUXEXENAME)
	INCLUDES += $(LINUXINCLUDES)
	LIBRARIES += $(LINUXLIBRARIES)
else
	EXENAME = $(WINDOWSEXENAME)
	INCLUDES += $(WINDOWSINCLUDES)
	LIBRARIES += $(WINDOWSLIBRARIES)
endif

ifeq ($(DEBUG), true)
	COMPILEFLAGS += -g
	LINKERFLAGS += -g
endif

run: all
	$(EXENAME)

cr:
	make all
	make run

rcr:
	make re
	make run

all: $(OBJECTS)
	$(CC) $(LINKERFLAGS) -o $(EXENAME) $(OBJECTS) $(LIBRARIES)

obj/%.o: src/%.cpp
	$(CC) $(INCLUDES) $(COMPILEFLAGS) -c -o $@ $<

optimized: COMPILEFLAGS += -$(OPTIMIZATIONLEVEL)
optimized: re

re: clean all

rm-backups:
	rm -f *~
	rm -f src/*~

rm-objects:
	rm -f obj/*.o

rm-exes:
	rm -f $(EXENAME)

clean: rm-objects rm-backups rm-exes
