#include "../common.h"

namespace Black {
std::vector<std::vector<int>> blocks(8);
std::vector<bool> en_passant(8);
bool turn = false;
int num_queens = 1;
std::vector<std::string> checker = {};
bool enpassant_check_killed = false;
bool is_AI = isBlackAI;
const int depth = 2;
bool screenshot = false;

std::vector<std::string> get_movesVec() {
  std::vector<std::string> moves = {};
  if (castle_criteria_K())
    moves.push_back("CK");
  if (castle_criteria_Q())
    moves.push_back("CQ");
  if (King.alive && !King.movelist.empty())
    moves.push_back("K");
  for (int i=0;i<num_queens;i++) {
    if (Queen.alive[i] && !Queen.movelist[i].empty())
      moves.push_back("Q" + str(i));
  }
  for (int i=0;i<8;i++) {
    if (Pawn.alive[i] && !Pawn.movelist[i].empty())
      moves.push_back("P" + str(i));
  }
  for (int i=0;i<2;i++) {
    if (Bishop.alive[i] && !Bishop.movelist[i].empty())
      moves.push_back("B" + str(i));
    if (Knight.alive[i] && !Knight.movelist[i].empty())
      moves.push_back("N" + str(i));
    if (Rook.alive[i] && !Rook.movelist[i].empty())
      moves.push_back("R" + str(i));
  }
  return moves;
}

std::map<std::string, std::vector<std::vector<int>>> get_moves() {
  std::map<std::string, std::vector<std::vector<int>>> moves = {};
  if (castle_criteria_K())
    moves["CK"] = {{0, 0}};
  if (castle_criteria_Q())
    moves["CQ"] = {{0, 0}};
  if (King.alive && !King.movelist.empty())
    moves["K"] = King.movelist;
  for (int i=0;i<num_queens;i++) {
    if (Queen.alive[i] && !Queen.movelist[i].empty())
      moves["Q" + str(i)] = Queen.movelist[i];
  }
  for (int i=0;i<8;i++) {
    if (Pawn.alive[i] && !Pawn.movelist[i].empty())
      moves["P" + str(i)] = Pawn.movelist[i];
  }
  for (int i=0;i<2;i++) {
    if (Bishop.alive[i] && !Bishop.movelist[i].empty())
      moves["B" + str(i)] = Bishop.movelist[i];
    if (Knight.alive[i] && !Knight.movelist[i].empty())
      moves["N" + str(i)] = Knight.movelist[i];
    if (Rook.alive[i] && !Rook.movelist[i].empty())
      moves["R" + str(i)] = Rook.movelist[i];
  }
  return moves;
}



void check_capture_screen() {
  if (screenshots_on && screenshot) {
    std::string path = "assets/screenshots/";
    path += str(Board.screenshot_num);
    path += ".png";
    take_screenshot(window, path);
    screenshot = false;
    Board.screenshot_num ++;
  }
}

void play() {
  if (is_AI)
    return;
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
      castle_K(false);
    else if (queue0 == kingpos && queue1 == q_rook && castle_criteria_Q())
      castle_Q(false);
    }
}

void handle_undo_promotion(int i, int row, int col) {
  pop_last_queen();
  revive("P" + str(i), row, col);
}

static void pop_last_queen() {
  num_queens --;
  blocks[Queen.row[num_queens]][Queen.col[num_queens]] = 0;
  Queen.row.resize(num_queens);
  Queen.col.resize(num_queens);
  Queen.x.resize(num_queens);
  Queen.y.resize(num_queens);
  Queen.alive.resize(num_queens);
  Queen.movelist.resize(num_queens);
  Queen.protecting_movelist.resize(num_queens);
}

void revive(std::string piece, int row, int col) {
  for (int i=0;i<num_queens;i++) {
    if (piece == "Q" + str(i)) {
      Queen.pure_move(i, row, col);
      Queen.alive[i] = 1;
    }
  }
  for (int i=0;i<8;i++) {
    if (piece == "P" + str(i)) {
      Pawn.pure_move(i, row, col);
      Pawn.alive[i] = 1;
    }
  }
  for (int i=0;i<2;i++) {
    if (piece == "B" + str(i)) {
      Bishop.pure_move(i, row, col);
      Bishop.alive[i] = 1;
    }
    if (piece == "N" + str(i)) {
      Knight.pure_move(i, row, col);
      Knight.alive[i] = 1;
    }
    if (piece == "R" + str(i)) {
      Rook.pure_move(i, row, col);
      Rook.alive[i] = 1;
    }
  }
}

void castle_K(bool is_undo) {
  undo.moved_from.push_back({King.row, King.col});
  King.move(0, 6);
  Rook.move(1, 0, 5);
  valid_move(is_undo, false, "CK", 0, 5);
}

void castle_Q(bool is_undo) {
  undo.moved_from.push_back({King.row, King.col});
  King.move(0, 2);
  Rook.move(0, 0, 3);
  valid_move(is_undo, false, "CQ", 0, 4);
}

bool castle_criteria_Q() {
  if (King.row != 0 || King.col != 4 || Rook.row[0] != 0 || Rook.col[1] != 0) return false;
  if (King.moved || Rook.moved[0] || !Rook.alive[0])
    return false;
  if (White::blocks[0][2] || White::blocks[0][3] || blocks[0][2] || blocks[0][3])
    return false;
  if (White::checker.size() >= 1)
    return false;
  if (in_opp_movelist(0, 2) || in_opp_movelist(0, 3))
    return false;
  return true;
}

bool castle_criteria_K() {
  if (King.row != 0 || King.col != 4 || Rook.row[0] != 0 || Rook.col[1] != 7) return false;
  if (King.moved || Rook.moved[1] || !Rook.alive[1])
    return false;
  if (White::blocks[0][5] || White::blocks[0][6] || blocks[0][5] || blocks[0][6])
    return false;
  if (White::checker.size() >= 1)
    return false;
  if (in_opp_movelist(0, 5) || in_opp_movelist(0, 6))
    return false;
  return true;
}

static bool in_opp_movelist(int row, int col) {
  std::vector<int> pos = {row, col};
  if (in(White::King.movelist, pos))
    return true;
  for (int i=0;i<White::num_queens;i++) {
    if (in(White::Queen.movelist[i], pos))
      return true;
  }
  for (int i=0;i<8;i++) {
    if (in(White::Pawn.hit_movelist[i], pos))
      return true;
  }
  for (int i=0;i<2;i++) {
    if (in(White::Bishop.movelist[i], pos))
      return true;
    if (in(White::Knight.movelist[i], pos))
      return true;
    if (in(White::Rook.movelist[i], pos))
      return true;
  }
  return false;
}

void move_piece(std::string piece, int row, int col) {
  assert(row >= 0 && row < 8 && col >= 0 && col < 8);
  std::vector<int> pos = {row, col};
  bool moved = false;
  checker.clear();
  bool killed = false;
  if (piece == "K" && in(King.movelist, pos)) {
    if (!Board.freeze) reset_enpassant();
    undo.moved_from.push_back({King.row, King.col});
    King.move(row, col);
    moved = true;
  }
  else if (piece == "K" && !in(King.movelist, pos)) {
    Sound.error();
    return;
  }
  for (int i=0;i<num_queens;i++) {
    if (piece == "Q" + std::to_string(i) && in(Queen.movelist[i], pos)) {
      if (!Board.freeze) reset_enpassant();
      undo.moved_from.push_back({Queen.row[i], Queen.col[i]});
      Queen.move(i, row, col);
      moved = true;
    }
    else if (piece == "Q" + std::to_string(i) && !in(Queen.movelist[i], pos)) {
      Sound.error();
      return;
    }
  }
  for (int i=0;i<8;i++) {
    if (piece == "P" + std::to_string(i) && in(Pawn.movelist[i], pos)) {
      if (!Board.freeze) reset_enpassant();
      undo.moved_from.push_back({Pawn.row[i], Pawn.col[i]});
      if (Pawn.row[i] == 4) {
        for (int k=0;k<8;k++) {
          if (White::en_passant[k]) {
            if (abs(Pawn.col[i] - White::Pawn.col[k]) == 1 && col == White::Pawn.col[k]) {
              check_kill(false, 4, White::Pawn.col[k]);
              enpassant_check_killed = true;
              killed = true;
            }
          }
        }
      }
      Pawn.move(i, row, col);
      if (row == 7)
        promote(i, row, col);
      moved = true;
    }
    else if (piece == "P" + std::to_string(i) && !in(Pawn.movelist[i], pos)) {
      Sound.error();
      return;
    }
  }
  for (int i=0;i<2;i++) {
    if (piece == "B" + std::to_string(i) && in(Bishop.movelist[i], pos)) {
      if (!Board.freeze) reset_enpassant();
      undo.moved_from.push_back({Bishop.row[i], Bishop.col[i]});
      Bishop.move(i, row, col);
      moved = true;
    }
    else if (piece == "B" + std::to_string(i) && !in(Bishop.movelist[i], pos)) {
      Sound.error();
      return;
    }
    if (piece == "N" + std::to_string(i) && in(Knight.movelist[i], pos)) {
      if (!Board.freeze) reset_enpassant();
      undo.moved_from.push_back({Knight.row[i], Knight.col[i]});
      Knight.move(i, row, col);
      moved = true;
    }
    else if (piece == "N" + std::to_string(i) && !in(Knight.movelist[i], pos)) {
      Sound.error();
      return;
    }
    if (piece == "R" + std::to_string(i) && in(Rook.movelist[i], pos)) {
      if (!Board.freeze) reset_enpassant();
      undo.moved_from.push_back({Rook.row[i], Rook.col[i]});
      Rook.move(i, row, col);
      moved = true;
    }
    else if (piece == "R" + std::to_string(i) && !in(Rook.movelist[i], pos)) {
      Sound.error();
      return;
    }
  }
  if (moved)
    valid_move(false, killed, piece, row, col);
}

void valid_move(bool is_undo, bool killed, std::string piece, int row, int col) {
  if (!killed && !is_undo && !Board.freeze)
    Sound.move();
  if (!is_undo) {
    Board.total_moves ++;
    undo.piece.push_back(piece);
    undo.color.push_back("B");
  }
  if (!enpassant_check_killed)
    check_kill(is_undo, row, col);
  Board.update_moves();
  check_pin();
  if (check_opp_checked() && !is_undo) {
    if (!Board.freeze)
      Sound.check();
    update_opp_movelists();
    if (opp_no_moves())
      Board.checkmate = true;
  }
  if (opp_no_moves() && !is_undo)
    Board.stalemate = true;
  if (!Board.freeze && screenshots_on) {
    screenshot = true;
  }
  if (!testing) {
    turn = false;
    White::turn = true;
  }
  enpassant_check_killed = false;
}

static bool opp_no_moves() {
  if (!White::King.movelist.empty())
    return false;
  for (int i=0;i<White::num_queens;i++) {
    if (!White::Queen.movelist[i].empty())
      return false;
  }
  for (int i=0;i<8;i++) {
    if (!White::Pawn.movelist[i].empty())
      return false;
  }
  for (int i=0;i<2;i++) {
    if (!White::Bishop.movelist[i].empty())
      return false;
    if (!White::Knight.movelist[i].empty())
      return false;
    if (!White::Rook.movelist[i].empty())
      return false;
  }
  return true;
}

void reset_enpassant() {
  for (int i=0;i<8;i++)
    en_passant[i] = 0;
}

static void check_pin() {
  Bishop.check_pin();
  Rook.check_pin();
  Queen.check_pin();
}

static void check_avoid_move() {
  std::vector<std::vector<int>> avoid_moves;
  for (int k=0;k<checker.size();k++) {
    for (int i=0;i<num_queens;i++) {
      if (checker[k] == "Q" + std::to_string(i))
        avoid_moves.push_back(Queen.get_avoid_move(i));
    }
    for (int i=0;i<2;i++) {
      if (checker[k] == "B" + std::to_string(i))
        avoid_moves.push_back(Bishop.get_avoid_move(i));
      if (checker[k] == "R" + std::to_string(i))
        avoid_moves.push_back(Rook.get_avoid_move(i));
    }
  }
  White::King.movelist = filter2(White::King.movelist, avoid_moves);
}

static void update_opp_movelists() {
  check_avoid_move();
  std::vector<std::vector<int>> check_movelist;
  for (int i=0;i<num_queens;i++) {
    if (checker[0] == "Q" + std::to_string(i))
      check_movelist = Queen.get_check_movelist(i);
  }
  for (int i=0;i<2;i++) {
    if (checker[0] == "B" + std::to_string(i))
      check_movelist = Bishop.get_check_movelist(i);
    else if (checker[0] == "R" + std::to_string(i))
      check_movelist = Rook.get_check_movelist(i);
    else if (checker[0] == "N" + std::to_string(i))
      check_movelist = {{Knight.row[i], Knight.col[i]}};
  }
  for (int i=0;i<8;i++) {
    if (checker[0] == "P" + std::to_string(i))
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
  // the rare case of double check: only the oppposite king can move! (this is because
  // no 1 piece can block both checks!)
  if (checker.size() > 1) {
    for (int i=0;i<8;i++) {
      White::Pawn.movelist[i].clear();
    }
    for (int i=0;i<2;i++) {
      White::Bishop.movelist[i].clear();
      White::Knight.movelist[i].clear();
      White::Rook.movelist[i].clear();
    }
    for (int i=0;i<White::num_queens;i++) {
      White::Queen.movelist[i].clear();
    }
  }
}

static bool check_opp_checked() {
  bool checked = false;
  for (int i=0;i<num_queens;i++) {
    if (in(Queen.movelist[i], {White::King.row, White::King.col})) {
      checker.push_back("Q" + std::to_string(i));
      checked = true;
    }
  }
  for (int i=0;i<8;i++) {
    if (in(Pawn.hit_movelist[i], {White::King.row, White::King.col})) {
      checker.push_back("P" + std::to_string(i));
      checked = true;
    }
  }
  for (int i=0;i<2;i++) {
    if (in(Bishop.movelist[i], {White::King.row, White::King.col})) {
      checker.push_back("B" + std::to_string(i));
      checked = true;
    }
    if (in(Knight.movelist[i], {White::King.row, White::King.col})) {
      checker.push_back("N" + std::to_string(i));
      checked = true;
    }
    if (in(Rook.movelist[i], {White::King.row, White::King.col})) {
      checker.push_back("R" + std::to_string(i));
      checked = true;
    }
  }
  return checked;
}

static void promote(int i, int row_, int col_) {
  int row = Pawn.row[i];
  int col = Pawn.col[i];
  kill(false, "P" + std::to_string(i), row, col);
  num_queens ++;
  Queen.row.push_back(row);
  Queen.col.push_back(col);
  Queen.x.push_back(col*UNIT);
  Queen.y.push_back(row*UNIT);
  Queen.alive.push_back(1);
  Queen.movelist.resize(num_queens);
  Queen.protecting_movelist.resize(num_queens);
  blocks[row_][col_] = 1;
}

static void check_kill(bool is_undo, int row, int col) {
  if (White::blocks[row][col] == 1 && !is_undo) {
    std::string piece = White::get_piece(row, col);
    White::kill(is_undo, piece, row, col);
    undo.killed.push_back(1);
    undo.killed_piece.push_back(piece);
    undo.killed_pos.push_back({row, col});
    undo.killed_color.push_back("W");
  }
  else if (White::blocks[row][col] == 0 && !is_undo) {
    undo.killed.push_back(0);
    undo.killed_piece.push_back("X");
    undo.killed_color.push_back("X");
    undo.killed_pos.push_back({-1, -1});
  }
}

std::string get_piece(int row, int col) {
  assert(row >= 0 && row < 8 && col >= 0 && col < 8);
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
  print("--Black blocks--");
  for (int i=0;i<8;i++) {
    for (int k=0;k<8;k++)
      printf("%d", blocks[i][k]);
    printf("\n");
  }
}

#ifdef DEBUGAI
void print_blocks_Log() {
  Log << ("--Black blocks--\n");
  for (int i=0;i<8;i++) {
    for (int k=0;k<8;k++)
      Log << blocks[i][k];
    Log << std::endl;
  }
}
#endif

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
    en_passant.push_back(0);
    blocks.push_back(std::vector<int>());
    for (int k=0;k<8;k++) {
      if (i == 0 || i == 1)
        blocks[i].push_back(1);
      else
        blocks[i].push_back(0);
    }
  }
  if (testing)
    turn = true;
}

void kill(bool is_undo, std::string piece, int row, int col) {
  blocks[row][col] = 0;
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
  if (!is_undo && !Board.freeze)
    Sound.kill();
}

} // namespace Black
