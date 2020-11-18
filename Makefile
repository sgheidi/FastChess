# generic Makefile for building program from source
# PCH: sudo g++ -Wall -fexceptions -g src/common.h

SOURCE= src/main.cc src/board.cc src/common.cc src/core/black_.cc src/core/black/bishop.cc
SOURCE+= src/core/black/knight.cc src/core/black/pawn.cc src/core/black/king.cc
SOURCE+= src/core/black/queen.cc src/core/black/rook.cc src/core/white_.cc
SOURCE+= src/core/white/bishop.cc src/core/white/knight.cc src/core/white/pawn.cc
SOURCE+= src/core/white/king.cc src/core/white/queen.cc src/core/white/rook.cc src/queue.cc
SOURCE+= src/media/sound.cc src/media/text.cc src/ai/helper.cc src/ai/black/search.cc src/ai/env.cc
SOURCE+= src/ai/black/eval.cc src/ai/white/eval.cc

CC= g++

EXECUTABLE= main

LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -fopenmp -lm -w -g

OBJECT= $(SOURCE:.cpp=.o)

all: $(OBJECT)
	$(CC) $(SOURCE) $(LDFLAGS) -o $(EXECUTABLE)

$(OBJECT):
	$(CC) -c -o $@ $(@:.o=.cpp)

clean:
	rm -f $(EXECUTABLE) *.o *.out
