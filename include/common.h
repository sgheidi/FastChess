#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>

#define X_RES 800
#define Y_RES 800
#define UNIT (X_RES/8)

#include "board.h"
#include "queue.h"
#include "pieces/black_.h"
#include "pieces/white_.h"

#include "pieces/black/bishop.h"
#include "pieces/black/knight.h"
#include "pieces/black/pawn.h"
#include "pieces/black/rook.h"
#include "pieces/black/queen.h"
#include "pieces/black/king.h"

#include "pieces/white/bishop.h"
#include "pieces/white/knight.h"
#include "pieces/white/pawn.h"
#include "pieces/white/rook.h"
#include "pieces/white/queen.h"
#include "pieces/white/king.h"

extern sf::RenderWindow window;

bool in(std::vector<int*> v, int* item);

#endif // COMMON_H
