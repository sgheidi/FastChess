#include "config.h"
#include "util.h"

#include "../board.h"
#include "../queue.h"
#include "../media/text.h"
#include "../media/sound.h"

#include "../core/black/bishop.h"
#include "../core/black/knight.h"
#include "../core/black/pawn.h"
#include "../core/black/rook.h"
#include "../core/black/queen.h"
#include "../core/black/king.h"

#include "../core/white/bishop.h"
#include "../core/white/knight.h"
#include "../core/white/pawn.h"
#include "../core/white/rook.h"
#include "../core/white/queen.h"
#include "../core/white/king.h"

#include "../core/white_.h"
#include "../core/black_.h"

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

// Global objects
Game_Board Board;
Click_Queue Queue;
Game_Sound Sound;
Game_Text Text;

namespace Black {
Bishop_Piece Bishop;
Knight_Piece Knight;
Pawn_Piece Pawn;
Rook_Piece Rook;
King_Piece King;
Queen_Piece Queen;
}

namespace White {
Bishop_Piece Bishop;
Knight_Piece Knight;
Pawn_Piece Pawn;
Rook_Piece Rook;
King_Piece King;
Queen_Piece Queen;
}
