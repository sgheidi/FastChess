#
# generic Makefile for building program from source
#

SOURCE= src/main.cc src/board.cc src/common.cc src/pieces/black_.cc src/pieces/black/bishop.cc
SOURCE+= src/pieces/black/knight.cc src/pieces/black/pawn.cc src/pieces/black/king.cc
SOURCE+= src/pieces/black/queen.cc src/pieces/black/rook.cc src/pieces/white_.cc
SOURCE+= src/pieces/white/bishop.cc src/pieces/white/knight.cc src/pieces/white/pawn.cc
SOURCE+= src/pieces/white/king.cc src/pieces/white/queen.cc src/pieces/white/rook.cc src/queue.cc

CC= g++

EXECUTABLE= main

LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lGLU -lGL -lm

OBJECT= $(SOURCE:.cpp=.o)

all: $(OBJECT)
	$(CC) $(SOURCE) $(LDFLAGS) -o $(EXECUTABLE)

$(OBJECT):
	$(CC) -c -o $@ $(@:.o=.cpp)

clean:
	rm -f $(EXECUTABLE) *.o *.out
