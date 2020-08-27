#include "../../include/common.h"

namespace Black {
std::vector<std::vector<int>> blocks(8);
bool turn = true;
int num_queens = 1;
std::string checker = "";

void play() {
  if (Queue.row.size() >= 2 && blocks[Queue.row[0]][Queue.col[0]] == 1 &&
  blocks[Queue.row[1]][Queue.col[1]] == 0) {
    std::string piece = get_piece(Queue.row[0], Queue.col[0]);
    move_piece(piece, Queue.row[1], Queue.col[1]);
    // std::cout << "Moving " << piece << " to ";
    // printf("(%d, %d)\n", Queue.row[1], Queue.col[1]);
  }
}

void move_piece(std::string piece, int row, int col) {
  assert(row >= 0 && row < 8 && col >= 0 && col < 8);
  std::vector<int> pos = {row, col};
  bool moved = false;
  checker = "";
  if (piece == "K" && in(King.movelist, pos)) {
    King.move(row, col);
    moved = true;
  }
  else if (piece == "K" && !in(King.movelist, pos)) {
    Sound.error();
  }
  for (int i=0;i<num_queens;i++) {
    if (piece == "Q" + std::to_string(i) && in(Queen.movelist[i], pos)) {
      Queen.move(i, row, col);
      moved = true;
    }
    else if (piece == "Q" + std::to_string(i) && !in(Queen.movelist[i], pos)) {
      Sound.error();
    }
  }
  for (int i=0;i<8;i++) {
    if (piece == "P" + std::to_string(i) && in(Pawn.movelist[i], pos)) {
      Pawn.move(i, row, col);
      if (row == 7) {
        promote(i);
      }
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
    if (piece == "R" + std::to_string(i) && in(Rook.movelist[i], pos)) {
      Rook.move(i, row, col);
      moved = true;
    }
    else if (piece == "R" + std::to_string(i) && !in(Rook.movelist[i], pos)) {
      Sound.error();
    }
  }
  if (moved) {
    Sound.move();
    check_kill(row, col);
    Board.update_moves();
    if (check_opp_checked()) {
      Sound.check();
      update_opp_movelists();
    }
    if (!testing) {
      turn = false;
      White::turn = true;
    }
  }
}

void check_avoid_move() {
  std::vector<int> avoid_move;
  for (int i=0;i<num_queens;i++) {
    if (checker == "Q" + std::to_string(i)) {
      avoid_move = Queen.get_avoid_move(i);
    }
  }
  for (int i=0;i<2;i++) {
    if (checker == "B" + std::to_string(i)) {
      avoid_move = Bishop.get_avoid_move(i);
    }
    if (checker == "R" + std::to_string(i)) {
      avoid_move = Rook.get_avoid_move(i);
    }
  }
  for (int i=0;i<White::King.movelist.size();i++) {
    if (White::King.movelist[i] == avoid_move)
      White::King.movelist[i].clear();
  }
}

void update_opp_movelists() {
  check_avoid_move();
  std::vector<std::vector<int>> check_movelist;
  for (int i=0;i<num_queens;i++) {
    if (checker == "Q" + std::to_string(i))
      check_movelist = Queen.get_check_movelist(i);
  }
  for (int i=0;i<2;i++) {
    if (checker == "B" + std::to_string(i))
      check_movelist = Bishop.get_check_movelist(i);
    else if (checker == "R" + std::to_string(i))
      check_movelist = Rook.get_check_movelist(i);
    else if (checker == "N" + std::to_string(i))
      check_movelist = {{Knight.row[i], Knight.col[i]}};
  }
  for (int i=0;i<8;i++) {
    if (checker == "P" + std::to_string(i))
      check_movelist = {{Pawn.row[i], Pawn.col[i]}};
  }
  for (int i=0;i<White::num_queens;i++) {
    White::Queen.movelist[i] = filter(White::Queen.movelist[i], check_movelist);
  }
  for (int i=0;i<2;i++) {
    White::Bishop.movelist[i] = filter(White::Bishop.movelist[i], check_movelist);
    White::Knight.movelist[i] = filter(White::Knight.movelist[i], check_movelist);
    White::Rook.movelist[i] = filter(White::Rook.movelist[i], check_movelist);
  }
  for (int i=0;i<8;i++) {
    White::Pawn.movelist[i] = filter(White::Pawn.movelist[i], check_movelist);
  }
}

bool check_opp_checked() {
  for (int i=0;i<num_queens;i++) {
    if (in(Queen.movelist[i], {White::King.row, White::King.col})) {
      checker = "Q" + std::to_string(i);
      return true;
    }
  }
  for (int i=0;i<8;i++) {
    if (in(Pawn.hit_movelist[i], {White::King.row, White::King.col})) {
      checker = "P" + std::to_string(i);
      return true;
    }
  }
  for (int i=0;i<2;i++) {
    if (in(Bishop.movelist[i], {White::King.row, White::King.col})) {
      checker = "B" + std::to_string(i);
      return true;
    }
    if (in(Knight.movelist[i], {White::King.row, White::King.col})) {
      checker = "N" + std::to_string(i);
      return true;
    }
    if (in(Rook.movelist[i], {White::King.row, White::King.col})) {
      checker = "R" + std::to_string(i);
      return true;
    }
  }
  return false;
}

void promote(int i) {
  int row = Pawn.row[i];
  int col = Pawn.col[i];
  kill("P" + std::to_string(i));
  num_queens ++;
  Queen.row.push_back(row);
  Queen.col.push_back(col);
  Queen.x.push_back(col*UNIT);
  Queen.y.push_back(row*UNIT);
  Queen.alive.push_back(1);
  Queen.movelist.resize(num_queens);
  Queen.protecting_movelist.resize(num_queens);
}

void check_kill(int row, int col) {
  if (White::blocks[row][col] == 1) {
    White::blocks[row][col] = 0;
    std::string piece = White::get_piece(row, col);
    White::kill(piece);
  }
}

std::string get_piece(int row, int col) {
  if (King.row == row && King.col == col)
    return "K";
  for (int i=0;i<num_queens;i++) {
    if (Queen.row[i] == row && Queen.col[i] == col)
      return "Q" + std::to_string(i);
  }
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

void kill(std::string piece) {
  if (piece == "K") {
    King.row = -1;
    King.col = -1;
    King.x = -1;
    King.y = -1;
    King.alive = false;
    King.movelist.clear();
  }
  for (int i=0;i<num_queens;i++) {
    if (piece == "Q" + std::to_string(i)) {
      Queen.row[i] = -1;
      Queen.col[i] = -1;
      Queen.x[i] = -1;
      Queen.y[i] = -1;
      Queen.alive[i] = false;
      Queen.movelist[i].clear();
      Queen.protecting_movelist[i].clear();
    }
  }
  for (int i=0;i<8;i++) {
    if (piece == "P" + std::to_string(i)) {
      Pawn.row[i] = -1;
      Pawn.col[i] = -1;
      Pawn.x[i] = -1;
      Pawn.y[i] = -1;
      Pawn.alive[i] = false;
      Pawn.movelist[i].clear();
      Pawn.hit_movelist[i].clear();
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
      Bishop.protecting_movelist[i].clear();
    }
    if (piece == "N" + std::to_string(i)) {
      Knight.row[i] = -1;
      Knight.col[i] = -1;
      Knight.x[i] = -1;
      Knight.y[i] = -1;
      Knight.alive[i] = false;
      Knight.movelist[i].clear();
      Knight.protecting_movelist[i].clear();
    }
    if (piece == "R" + std::to_string(i)) {
      Rook.row[i] = -1;
      Rook.col[i] = -1;
      Rook.x[i] = -1;
      Rook.y[i] = -1;
      Rook.alive[i] = false;
      Rook.movelist[i].clear();
      Rook.protecting_movelist[i].clear();
    }
  }
  Sound.kill();
}

} // namespace Black
