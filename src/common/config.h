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
