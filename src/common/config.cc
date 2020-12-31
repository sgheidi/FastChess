#include "config.h"

const std::string env = "";
const bool testing = false;
const bool isBlackAI = true;
const bool screenshots_on = false;

// for useful outputs relating to AI eval
const bool verbose = true;

// more verbose outputs relating to AI search in CLI
const bool verbose2 = false;

#ifdef DEBUGAI
std::ofstream Log("debug.log");
#endif
struct undo_stack undo = {
  {},
  {},
  {},
  {},
  {},
  {},
  {}
};
sf::RenderWindow window(sf::VideoMode(X_RES, Y_RES), "FastChess");
