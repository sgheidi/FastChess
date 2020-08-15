#include "../../include/common.h"

namespace Black {
std::vector<std::vector<int>> blocks(8);
bool turn = true;

void kill(std::string piece) {
  if (piece == "K") {
    King.row = -1;
    King.col = -1;
    King.x = -1;
    King.y = -1;
    King.alive = false;
    King.movelist.clear();
  }
  else if (piece == "Q") {
    Queen.row = -1;
    Queen.col = -1;
    Queen.x = -1;
    Queen.y = -1;
    Queen.alive = false;
    Queen.movelist.clear();
  }
  for (int i=0;i<8;i++) {
    if (piece == "P" + std::to_string(i)) {
      Pawn.row[i] = -1;
      Pawn.col[i] = -1;
      Pawn.x[i] = -1;
      Pawn.y[i] = -1;
      Pawn.alive[i] = false;
      Pawn.movelist[i].clear();
    }
  }
  for (int i=0;i<2;i++) {
    if (piece == "B" + std::to_string(i)) {
      Bishop.row[i] = -1;
      Bishop.col[i] = -1;
      Bishop.x[i] = -1;
      Bishop.y[i] = -1;
      Bishop.alive[i] = false;
      Bishop.movelist[i].clear();
    }
    if (piece == "N" + std::to_string(i)) {
      Knight.row[i] = -1;
      Knight.col[i] = -1;
      Knight.x[i] = -1;
      Knight.y[i] = -1;
      Knight.alive[i] = false;
      Knight.movelist[i].clear();
    }
    if (piece == "R" + std::to_string(i)) {
      Rook.row[i] = -1;
      Rook.col[i] = -1;
      Rook.x[i] = -1;
      Rook.y[i] = -1;
      Rook.alive[i] = false;
      Rook.movelist[i].clear();
    }
  }
  Sound.kill();
}

void play() {

  turn = false;
}

std::string get_piece(int row, int col) {
  if (King.row == row && King.col == col)
    return "K";
  else if (Queen.row == row && Queen.col == col)
    return "Q";
  for (int i=0;i<8;i++) {
    if (Pawn.row[i] == row && Pawn.col[i] == col)
      return "P" + std::to_string(i);
  }
  for (int i=0;i<2;i++) {
    if (Bishop.row[i] == row && Bishop.col[i] == col)
      return "B" + std::to_string(i);
    else if (Knight.row[i] == row && Knight.col[i] == col)
      return "N" + std::to_string(i);
    else if (Rook.row[i] == row && Rook.col[i] == col)
      return "R" + std::to_string(i);
  }
}

void print_blocks() {
  for (int i=0;i<8;i++) {
    for (int k=0;k<8;k++)
      printf("%d", blocks[i][k]);
    printf("\n");
  }
}

void show() {
  Bishop.show();
  Knight.show();
  Pawn.show();
  Rook.show();
  King.show();
  Queen.show();
}

void init() {
  for (int i=0;i<8;i++) {
    blocks.push_back(std::vector<int>());
    for (int k=0;k<8;k++) {
      if (i == 0 || i == 1)
        blocks[i].push_back(1);
      else
        blocks[i].push_back(0);
    }
  }
}

} // namespace Black
