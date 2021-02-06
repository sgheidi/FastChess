#ifndef COMMON_CONFIG_H
#define COMMON_CONFIG_H

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

// dump verbose AI search logs in file debug.log
// #define DEBUGAI

// take screenshots of each move, save in `assets` folder
// #define SCREENSHOTS_ON

// flag for toggling no turns
// #define IS_TESTING

// Black AI
#define IS_BLACK_AI

// for useful outputs relating to AI eval
#ifdef IS_BLACK_AI
#define VERBOSE
#endif

// more verbose outputs relating to AI search in CLI
// #define VERBOSE2

// game environments can be used to test AI at a particular position
#define GAME_ENV ""

#define X_RES 600
#define Y_RES 600
#define UNIT (X_RES/8)

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

#endif // COMMON_CONFIG_H
