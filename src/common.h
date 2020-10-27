#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

extern bool testing;
extern bool verbose;
extern std::string env;
struct undo_stack {
  std::vector<std::vector<int>> moved_from;
  std::vector<std::string> piece;
  std::vector<std::string> color;
  std::vector<bool> killed;
  std::vector<std::string> killed_piece;
  std::vector<std::vector<int>> killed_pos;
  std::vector<std::string> killed_color;
};
extern struct undo_stack undo;
void init(std::string env);
std::string str(int n);
void print_map(std::map<std::string, std::vector<std::vector<int>>> map);
void print(std::string s);
std::vector<std::vector<int>>
filter2(std::vector<std::vector<int>> v1, std::vector<std::vector<int>> v2);
std::vector<std::vector<int>>
filter(std::vector<std::vector<int>> v1, std::vector<std::vector<int>> v2);
void print_v2(std::vector<std::vector<int>> v);
void print_v3(std::vector<std::vector<std::vector<int>>> v);
bool in(std::vector<std::vector<int>> v, std::vector<int> item);

template <typename T>
inline void print_v1(T v) {
  printf("vec1d...\n");
  for (int i=0;i<v.size();i++) {
    std::cout << v[i];
  }
  printf("\n");
}

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

#include "ai/helper.h"
#include "ai/black.h"

extern sf::RenderWindow window;

#endif // COMMON_H
