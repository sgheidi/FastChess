#include "../include/common.h"

// return true if item in vector
bool in(std::vector<std::vector<int>> v, std::vector<int> item) {
  if (std::find(v.begin(), v.end(), item) != v.end())
    return true;
  return false;
}

Game_Board Board;
Black_Pieces Black;
White_Pieces White;
Click_Queue Queue;
Game_Sound Sound;

Black_Bishop BBishop;
Black_Knight BKnight;
Black_Pawn BPawn;
Black_Rook BRook;
Black_King BKing;
Black_Queen BQueen;

White_Bishop WBishop;
White_Knight WKnight;
White_Pawn WPawn;
White_Rook WRook;
White_King WKing;
White_Queen WQueen;

sf::RenderWindow window(sf::VideoMode(X_RES, Y_RES), "FastChess");
