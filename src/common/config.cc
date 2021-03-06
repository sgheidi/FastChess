#include <iostream>
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "config.h"
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

#ifdef DEBUGAI
std::ofstream log("debug.log");
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

// Global game objects
Game_Board board;
Click_Queue queue;
Game_Sound sound;
Game_Text text;

namespace black {
Bishop_Piece bishop;
Knight_Piece knight;
Pawn_Piece pawn;
Rook_Piece rook;
King_Piece king;
Queen_Piece queen;
}

namespace white {
Bishop_Piece bishop;
Knight_Piece knight;
Pawn_Piece pawn;
Rook_Piece rook;
King_Piece king;
Queen_Piece queen;
}
