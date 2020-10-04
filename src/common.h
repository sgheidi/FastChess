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
std::string str(int n);
void print(std::string s);
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
#include "media/sound.h"
#include "core/piece.h"
#include "media/text.h"

#include "core/black/bishop.h"
#include "core/black/knight.h"
#include "core/black/pawn.h"
#include "core/black/rook.h"
#include "core/black/queen.h"
#include "core/black/king.h"

#include "core/white/bishop.h"
#include "core/white/knight.h"
#include "core/white/pawn.h"
#include "core/white/rook.h"
#include "core/white/queen.h"
#include "core/white/king.h"

#include "core/white_.h"
#include "core/black_.h"

extern sf::RenderWindow window;

#endif // COMMON_H