#include "../common.h"

namespace White {

void play() {
  if (Queue.row.size() >= 2 && blocks[Queue.row[0]][Queue.col[0]] == 1 &&
  blocks[Queue.row[1]][Queue.col[1]] == 0) {
    std::string piece = get_piece(Queue.row[0], Queue.col[0]);
    move_piece(piece, Queue.row[1], Queue.col[1]);
  }
  if (Queue.row.size() >= 2) {
    std::vector<int> kingpos = {King.row, King.col};
    std::vector<int> k_rook = {Rook.row[1], Rook.col[1]};
    std::vector<int> q_rook = {Rook.row[0], Rook.col[0]};
    std::vector<int> queue0 = {Queue.row[0], Queue.col[0]};
    std::vector<int> queue1 = {Queue.row[1], Queue.col[1]};
    if (queue0 == kingpos && queue1 == k_rook && castle_criteria_K())
      castle_K();
    }
}

void castle_K() {
  std::cout << "Test?" << std::endl;
}

bool castle_criteria_K() {
  return true;
  // if (King.moved || Rook.moved[1])
  //   return false;
  // if (Black::blocks[7][6] || Black::blocks[7][5] || blocks[7][6] || blocks[7][5])
  //   return false;
  // if (Black::checker != "")
  //   return false;
  // if (in_movelist(7, 6) || in_movelist(7, 5))
  //   return false;
  // return true;
}

bool in_movelist(int row, int col) {
  std::vector<int> pos = {row, col};
  if (in(Black::King.movelist, pos))
    return true;
  for (int i=0;i<Black::num_queens;i++) {
    if (in(Black::Queen.movelist[i], pos))
      return true;
  }
  for (int i=0;i<8;i++) {
    if (in(Black::Pawn.movelist[i], pos))
      return true;
  }
  for (int i=0;i<2;i++) {
    if (in(Black::Bishop.movelist[i], pos))
      return true;
    if (in(Black::Knight.movelist[i], pos))
      return true;
    if (in(Black::Rook.movelist[i], pos))
      return true;
  }
  return false;
}

void move_piece(std::string piece, int row, int col) {
  assert(row >= 0 && row < 8 && col >= 0 && col < 8);
  std::vector<int> pos = {row, col};
  bool moved = false;
  Pawn.en_passant.clear();
  checker = "";
  if (piece == "K" && in(King.movelist, pos)) {
    undo.moved_from.push_back({King.row, King.col});
    King.move(row, col);
    moved = true;
  }
  else if (piece == "K" && !in(King.movelist, pos)) {
    Sound.error();
  }
  for (int i=0;i<num_queens;i++) {
    if (piece == "Q" + std::to_string(i) && in(Queen.movelist[i], pos)) {
      undo.moved_from.push_back({Queen.row[i], Queen.col[i]});
      Queen.move(i, row, col);
      moved = true;
    }
    else if (piece == "Q" + std::to_string(i) && !in(Queen.movelist[i], pos)) {
      Sound.error();
    }
  }
  for (int i=0;i<8;i++) {
    if (piece == "P" + std::to_string(i) && in(Pawn.movelist[i], pos)) {
      undo.moved_from.push_back({Pawn.row[i], Pawn.col[i]});
      Pawn.move(i, row, col);
      if (row == 0) {
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
      undo.moved_from.push_back({Bishop.row[i], Bishop.col[i]});
      Bishop.move(i, row, col);
      moved = true;
    }
    else if (piece == "B" + std::to_string(i) && !in(Bishop.movelist[i], pos)) {
      Sound.error();
    }
    if (piece == "N" + std::to_string(i) && in(Knight.movelist[i], pos)) {
      undo.moved_from.push_back({Knight.row[i], Knight.col[i]});
      Knight.move(i, row, col);
      moved = true;
    }
    else if (piece == "N" + std::to_string(i) && !in(Knight.movelist[i], pos)) {
      Sound.error();
    }
    if (piece == "R" + std::to_string(i) && in(Rook.movelist[i], pos)) {
      undo.moved_from.push_back({Rook.row[i], Rook.col[i]});
      Rook.move(i, row, col);
      moved = true;
    }
    else if (piece == "R" + std::to_string(i) && !in(Rook.movelist[i], pos)) {
      Sound.error();
    }
  }
  if (moved) {
    Board.total_moves ++;
    Sound.move();
    undo.piece.push_back(piece);
    undo.color.push_back("W");
    Board.arrow({undo.moved_from[Board.total_moves-1][0], undo.moved_from[Board.total_moves-1][1]}, {row, col});
    check_kill(row, col);
    Board.update_moves();
    if (check_opp_checked()) {
      Sound.check();
      update_opp_movelists();
      if (opp_no_moves())
        Board.checkmate = true;
    }
    if (opp_no_moves())
      Board.stalemate = true;
    check_pin();
    if (!testing) {
      turn = false;
      Black::turn = true;
    }
  }
}

bool opp_no_moves() {
  if (!Black::King.movelist.empty())
    return false;
  for (int i=0;i<num_queens;i++) {
    if (!Black::Queen.movelist[i].empty())
      return false;
  }
  for (int i=0;i<8;i++) {
    if (!Black::Pawn.movelist[i].empty())
      return false;
  }
  for (int i=0;i<2;i++) {
    if (!Black::Bishop.movelist[i].empty())
      return false;
    if (!Black::Knight.movelist[i].empty())
      return false;
    if (!Black::Rook.movelist[i].empty())
      return false;
  }
  return true;
}

void check_pin() {
  Bishop.check_pin();
  Rook.check_pin();
  Queen.check_pin();
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
  for (int i=0;i<Black::King.movelist.size();i++) {
    if (Black::King.movelist[i] == avoid_move)
      Black::King.movelist.erase(Black::King.movelist.begin() + i);
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
  for (int i=0;i<Black::num_queens;i++) {
    Black::Queen.movelist[i] = filter(Black::Queen.movelist[i], check_movelist);
  }
  for (int i=0;i<2;i++) {
    Black::Bishop.movelist[i] = filter(Black::Bishop.movelist[i], check_movelist);
    Black::Knight.movelist[i] = filter(Black::Knight.movelist[i], check_movelist);
    Black::Rook.movelist[i] = filter(Black::Rook.movelist[i], check_movelist);
  }
  for (int i=0;i<8;i++) {
    Black::Pawn.movelist[i] = filter(Black::Pawn.movelist[i], check_movelist);
  }
}

bool check_opp_checked() {
  for (int i=0;i<num_queens;i++) {
    if (in(Queen.movelist[i], {Black::King.row, Black::King.col})) {
      checker = "Q" + std::to_string(i);
      return true;
    }
  }
  for (int i=0;i<8;i++) {
    if (in(Pawn.hit_movelist[i], {Black::King.row, Black::King.col})) {
      checker = "P" + std::to_string(i);
      return true;
    }
  }
  for (int i=0;i<2;i++) {
    if (in(Bishop.movelist[i], {Black::King.row, Black::King.col})) {
      checker = "B" + std::to_string(i);
      return true;
    }
    if (in(Knight.movelist[i], {Black::King.row, Black::King.col})) {
      checker = "N" + std::to_string(i);
      return true;
    }
    if (in(Rook.movelist[i], {Black::King.row, Black::King.col})) {
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
  if (Black::blocks[row][col] == 1) {
    Black::blocks[row][col] = 0;
    std::string piece = Black::get_piece(row, col);
    Black::kill(piece);
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
      if (i == 6 || i == 7)
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
std::vector<std::vector<int>> blocks(8);
bool turn = true;
int num_queens = 1;
std::string checker = "";
} // namespace White
