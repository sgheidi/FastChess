#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

struct undo_stack {
  std::vector<std::vector<int>> moved_from;
  std::vector<std::string> piece;
  std::vector<std::string> color;
};
extern struct undo_stack undo;
extern bool testing;
std::vector<std::vector<int>>
filter2(std::vector<std::vector<int>> v1, std::vector<std::vector<int>> v2);
std::vector<std::vector<int>>
filter(std::vector<std::vector<int>> v1, std::vector<std::vector<int>> v2);
void print_v1(std::vector<int> v);
void print_v3(std::vector<std::vector<std::vector<int>>> v);
bool in(std::vector<std::vector<int>> v, std::vector<int> item);
void print_v2(std::vector<std::vector<int>> v);

#define X_RES 800
#define Y_RES 800
#define UNIT (X_RES/8)

#include "board.h"
#include "queue.h"
#include "sound.h"
#include "pieces/piece.h"
#include "text.h"

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

#include "pieces/white_.h"
#include "pieces/black_.h"

extern sf::RenderWindow window;

#endif // COMMON_H
