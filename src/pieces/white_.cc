#include "../../include/common.h"

void White_Pieces::play() {
  if (Queue.row.size() >= 2 && White.blocks[Queue.row[0]][Queue.col[0]] == 1 &&
  White.blocks[Queue.row[1]][Queue.col[1]] == 0) {
    std::string piece = get_piece(Queue.row[0], Queue.col[0]);
    move_piece(piece, Queue.row[1], Queue.col[1]);
    // std::cout << "Moving " << piece << " to ";
    // printf("(%d, %d)\n", Queue.row[1], Queue.col[1]);
    // turn = false;
  }
}

void White_Pieces::move_piece(std::string piece, int row, int col) {
  assert(row >= 0 && row < 8 && col >= 0 && col < 8);
  std::vector<int> pos = {row, col};
  if (piece == "K") {
    WKing.move(row, col);
  }
  else if (piece == "Q")
    WQueen.move(row, col);
  for (int i=0;i<8;i++) {
    if (piece == "P" + std::to_string(i) && in(WPawn.movelist[i], pos)) {
      WPawn.move(i, row, col);
      Sound.move();
    }
    else if (piece == "P" + std::to_string(i) && !in(WPawn.movelist[i], pos)) {
      Sound.error();
    }
  }
  for (int i=0;i<2;i++) {
    if (piece == "B" + std::to_string(i))
      WBishop.move(i, row, col);
    else if (piece == "N" + std::to_string(i))
      WKnight.move(i, row, col);
    else if (piece == "R" + std::to_string(i))
      WRook.move(i, row, col);
  }
  Board.update_moves();
}

std::string White_Pieces::get_piece(int row, int col) {
  if (WKing.row == row && WKing.col == col)
    return "K";
  else if (WQueen.row == row && WQueen.col == col)
    return "Q";
  for (int i=0;i<8;i++) {
    if (WPawn.row[i] == row && WPawn.col[i] == col)
      return "P" + std::to_string(i);
  }
  for (int i=0;i<2;i++) {
    if (WBishop.row[i] == row && WBishop.col[i] == col)
      return "B" + std::to_string(i);
    else if (WKnight.row[i] == row && WKnight.col[i] == col)
      return "N" + std::to_string(i);
    else if (WRook.row[i] == row && WRook.col[i] == col)
      return "R" + std::to_string(i);
  }
}

void White_Pieces::print_blocks() {
  for (int i=0;i<8;i++) {
    for (int k=0;k<8;k++)
      printf("%d", blocks[i][k]);
    printf("\n");
  }
}

void White_Pieces::show() {
  WBishop.show();
  WKnight.show();
  WPawn.show();
  WRook.show();
  WKing.show();
  WQueen.show();
}
