#include "../include/common.h"

// return true if item in vector
bool in(std::vector<std::vector<int>> v, std::vector<int> item) {
  if (std::find(v.begin(), v.end(), item) != v.end())
    return true;
  return false;
}

Game_Board Board;
Click_Queue Queue;
Game_Sound Sound;

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

sf::RenderWindow window(sf::VideoMode(X_RES, Y_RES), "FastChess");
