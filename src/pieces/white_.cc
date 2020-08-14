#include "../../include/common.h"

namespace White {

std::vector<std::vector<int>> blocks(8);
bool turn = true;

void play() {
  if (Queue.row.size() >= 2 && blocks[Queue.row[0]][Queue.col[0]] == 1 &&
  blocks[Queue.row[1]][Queue.col[1]] == 0) {
    std::string piece = get_piece(Queue.row[0], Queue.col[0]);
    move_piece(piece, Queue.row[1], Queue.col[1]);
    // std::cout << "Moving " << piece << " to ";
    // printf("(%d, %d)\n", Queue.row[1], Queue.col[1]);
    // turn = false;
  }
}

void move_piece(std::string piece, int row, int col) {
  assert(row >= 0 && row < 8 && col >= 0 && col < 8);
  std::vector<int> pos = {row, col};
  bool moved = false;
  if (piece == "K") {
    King.move(row, col);
    moved = true;
  }
  else if (piece == "Q") {
    Queen.move(row, col);
    moved = true;
  }
  for (int i=0;i<8;i++) {
    if (piece == "P" + std::to_string(i) && in(Pawn.movelist[i], pos)) {
      Pawn.move(i, row, col);
      moved = true;
    }
    else if (piece == "P" + std::to_string(i) && !in(Pawn.movelist[i], pos)) {
      Sound.error();
    }
  }
  for (int i=0;i<2;i++) {
    if (piece == "B" + std::to_string(i) && in(Bishop.movelist[i], pos)) {
      Bishop.move(i, row, col);
      moved = true;
    }
    else if (piece == "B" + std::to_string(i) && !in(Bishop.movelist[i], pos)) {
      Sound.error();
    }
    if (piece == "N" + std::to_string(i) && in(Knight.movelist[i], pos)) {
      Knight.move(i, row, col);
      moved = true;
    }
    else if (piece == "N" + std::to_string(i) && !in(Knight.movelist[i], pos)) {
      Sound.error();
    }
    if (piece == "R" + std::to_string(i)) {
      Rook.move(i, row, col);
      moved = true;
    }
  }
  if (moved) {
    Board.update_moves();
    Sound.move();
    // check_kill(row, col);
  }
}

void check_kill(int row, int col) {
  if (Black::blocks[row][col] == 1) {
    // std::string piece = Black.get_piece(row, col);
    // Black.kill(piece);
  }
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
      if (i == 6 || i == 7)
        blocks[i].push_back(1);
      else
        blocks[i].push_back(0);
    }
  }
}

} // namespace White
