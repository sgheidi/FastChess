#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>
#include <random>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

// uncomment this to dump verbose AI search logs in file debug.log
// #define DEBUGAI

#define X_RES 600
#define Y_RES 600
#define UNIT (X_RES/8)

extern const bool screenshots_on;
extern const bool testing;
extern const bool verbose2;
extern const bool verbose;
extern const std::string env;
extern const bool isBlackAI;
extern std::ofstream Log;
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
extern sf::RenderWindow window;

void take_screenshot(const sf::RenderWindow& window, const std::string& filename);
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

#ifdef DEBUGAI
template <typename T>
inline void print_v1_Log(T v) {
  for (int i=0;i<v.size();i++) {
    Log << v[i];
  }
  Log << std::endl;
}
#endif

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
#include "ai/black/eval.h"
#include "ai/white/eval.h"
#include "ai/black/search.h"

#endif // COMMON_H
