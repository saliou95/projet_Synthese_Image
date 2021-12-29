EXT = cpp
CXX=g++
CFLAGS=-Wall -I/usr/local/include
CFLAGS=
#LDFLAGS= -lGL -lGLEW -lGLU -lglut  -larmadillo
#LDFLAGS= -lGL -lGLU -lGLEW -lglut -lm 
LDFLAGS= -lGL -lGLU -lGLEW -lglut

#SRC=saisieinteractive.cpp courbe.cpp
SRC=$(wildcard *.$(EXT))
# $(wildcard ./utilstexture/*.$(EXT))
OBJ = $(SRC:.$(EXT)=.o)

DEBUBFLAG=-g

BIN=./
EXEC=main

all: $(EXEC)

$(EXEC): $(OBJ)
		$(CXX)  -o $(BIN)$@ $^ $(LDFLAGS)

%.o: %.cpp
		$(CXX)  -o $@ -c $< $(CFLAGS)


clean:
		rm -rf *.o

mrproper: clean
		rm -rf $(BIN)$(EXEC)

