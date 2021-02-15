#include <assert.h>

#include "../common/config.h"
#include "../common/util.h"

#include "../board.h"
#include "../queue.h"
#include "../media/sound.h"

#include "black/bishop.h"
#include "black/knight.h"
#include "black/pawn.h"
#include "black/rook.h"
#include "black/queen.h"
#include "black/king.h"

#include "white/bishop.h"
#include "white/knight.h"
#include "white/pawn.h"
#include "white/rook.h"
#include "white/queen.h"
#include "white/king.h"

#include "white_.h"
#include "black_.h"

namespace black {
std::vector<std::vector<int>> blocks(8);
std::vector<bool> en_passant(8);
bool turn = false;
int num_queens = 1;
std::vector<std::string> checker = {};
const int depth = 2;
bool screenshot = false;

namespace {
bool enpassant_check_killed = false;

void pop_last_queen() {
  num_queens --;
  blocks[queen.row[num_queens]][queen.col[num_queens]] = 0;
  queen.row.resize(num_queens);
  queen.col.resize(num_queens);
  queen.x.resize(num_queens);
  queen.y.resize(num_queens);
  queen.alive.resize(num_queens);
  queen.movelist.resize(num_queens);
  queen.protecting_movelist.resize(num_queens);
}

bool in_opp_movelist(int row, int col) {
  const std::vector<int> pos = {row, col};
  if (in(white::king.movelist, pos))
    return true;
  for (int i=0;i<white::num_queens;i++) {
    if (in(white::queen.movelist[i], pos))
      return true;
  }
  for (int i=0;i<8;i++) {
    if (in(white::pawn.hit_movelist[i], pos))
      return true;
  }
  for (int i=0;i<2;i++) {
    if (in(white::bishop.movelist[i], pos) || in(white::knight.movelist[i], pos) || in(white::rook.movelist[i], pos))
      return true;
  }
  return false;
}

bool opp_no_moves() {
  if (!white::king.movelist.empty())
    return false;
  for (int i=0;i<white::num_queens;i++) {
    if (!white::queen.movelist[i].empty())
      return false;
  }
  for (int i=0;i<8;i++) {
    if (!white::pawn.movelist[i].empty())
      return false;
  }
  for (int i=0;i<2;i++) {
    if (!white::bishop.movelist[i].empty() || !white::knight.movelist[i].empty() || !white::rook.movelist[i].empty())
      return false;
  }
  return true;
}

void check_pin() {
  bishop.check_pin();
  rook.check_pin();
  queen.check_pin();
}

void check_avoid_move() {
  std::vector<std::vector<int>> avoid_moves;
  for (int k=0;k<checker.size();k++) {
    for (int i=0;i<num_queens;i++) {
      if (checker[k] == "Q" + std::to_string(i))
        avoid_moves.push_back(queen.get_avoid_move(i));
    }
    for (int i=0;i<2;i++) {
      if (checker[k] == "B" + std::to_string(i))
        avoid_moves.push_back(bishop.get_avoid_move(i));
      if (checker[k] == "R" + std::to_string(i))
        avoid_moves.push_back(rook.get_avoid_move(i));
    }
  }
  white::king.movelist = filter2(white::king.movelist, avoid_moves);
}

void update_opp_movelists() {
  check_avoid_move();
  std::vector<std::vector<int>> check_movelist;
  for (int i=0;i<num_queens;i++) {
    if (checker[0] == "Q" + std::to_string(i))
      check_movelist = queen.get_check_movelist(i);
  }
  for (int i=0;i<2;i++) {
    if (checker[0] == "B" + std::to_string(i))
      check_movelist = bishop.get_check_movelist(i);
    else if (checker[0] == "R" + std::to_string(i))
      check_movelist = rook.get_check_movelist(i);
    else if (checker[0] == "N" + std::to_string(i))
      check_movelist = {{knight.row[i], knight.col[i]}};
  }
  for (int i=0;i<8;i++) {
    if (checker[0] == "P" + std::to_string(i))
      check_movelist = {{pawn.row[i], pawn.col[i]}};
  }
  for (int i=0;i<white::num_queens;i++) {
    white::queen.movelist[i] = filter(white::queen.movelist[i], check_movelist);
  }
  for (int i=0;i<2;i++) {
    white::bishop.movelist[i] = filter(white::bishop.movelist[i], check_movelist);
    white::knight.movelist[i] = filter(white::knight.movelist[i], check_movelist);
    white::rook.movelist[i] = filter(white::rook.movelist[i], check_movelist);
  }
  for (int i=0;i<8;i++) {
    white::pawn.movelist[i] = filter(white::pawn.movelist[i], check_movelist);
  }
  // the rare case of double check: only the oppposite king can move! (this is because no 1 piece can block both checks)
  if (checker.size() > 1) {
    for (int i=0;i<8;i++) {
      white::pawn.movelist[i].clear();
    }
    for (int i=0;i<2;i++) {
      white::bishop.movelist[i].clear();
      white::knight.movelist[i].clear();
      white::rook.movelist[i].clear();
    }
    for (int i=0;i<white::num_queens;i++) {
      white::queen.movelist[i].clear();
    }
  }
}

bool check_opp_checked() {
  bool checked = false;
  for (int i=0;i<num_queens;i++) {
    if (in(queen.movelist[i], {white::king.row, white::king.col})) {
      checker.push_back("Q" + std::to_string(i));
      checked = true;
    }
  }
  for (int i=0;i<8;i++) {
    if (in(pawn.hit_movelist[i], {white::king.row, white::king.col})) {
      checker.push_back("P" + std::to_string(i));
      checked = true;
    }
  }
  for (int i=0;i<2;i++) {
    if (in(bishop.movelist[i], {white::king.row, white::king.col})) {
      checker.push_back("B" + std::to_string(i));
      checked = true;
    }
    if (in(knight.movelist[i], {white::king.row, white::king.col})) {
      checker.push_back("N" + std::to_string(i));
      checked = true;
    }
    if (in(rook.movelist[i], {white::king.row, white::king.col})) {
      checker.push_back("R" + std::to_string(i));
      checked = true;
    }
  }
  return checked;
}

void promote(int i, int row_, int col_) {
  const int row = pawn.row[i];
  const int col = pawn.col[i];
  kill(false, "P" + std::to_string(i), row, col);
  num_queens ++;
  queen.row.push_back(row);
  queen.col.push_back(col);
  queen.x.push_back(col*UNIT);
  queen.y.push_back(row*UNIT);
  queen.alive.push_back(1);
  queen.movelist.resize(num_queens);
  queen.protecting_movelist.resize(num_queens);
  blocks[row_][col_] = 1;
}

void check_kill(bool is_undo, int row, int col) {
  if (white::blocks[row][col] == 1 && !is_undo) {
    std::string piece = white::get_piece(row, col);
    white::kill(is_undo, piece, row, col);
    undo.killed.push_back(1);
    undo.killed_piece.push_back(piece);
    undo.killed_pos.push_back({row, col});
    undo.killed_color.push_back("W");
  }
  else if (white::blocks[row][col] == 0 && !is_undo) {
    undo.killed.push_back(0);
    undo.killed_piece.push_back("X");
    undo.killed_color.push_back("X");
    undo.killed_pos.push_back({-1, -1});
  }
}
} // namespace

std::map<std::string, std::vector<std::vector<int>>> get_moves() {
  std::map<std::string, std::vector<std::vector<int>>> moves = {};
  if (castle_criteria_K())
    moves["CK"] = {{0, 0}};
  if (castle_criteria_Q())
    moves["CQ"] = {{0, 0}};
  if (king.alive && !king.movelist.empty())
    moves["K"] = king.movelist;
  for (int i=0;i<num_queens;i++) {
    if (queen.alive[i] && !queen.movelist[i].empty())
      moves["Q" + str(i)] = queen.movelist[i];
  }
  for (int i=0;i<8;i++) {
    if (pawn.alive[i] && !pawn.movelist[i].empty())
      moves["P" + str(i)] = pawn.movelist[i];
  }
  for (int i=0;i<2;i++) {
    if (bishop.alive[i] && !bishop.movelist[i].empty())
      moves["B" + str(i)] = bishop.movelist[i];
    if (knight.alive[i] && !knight.movelist[i].empty())
      moves["N" + str(i)] = knight.movelist[i];
    if (rook.alive[i] && !rook.movelist[i].empty())
      moves["R" + str(i)] = rook.movelist[i];
  }
  return moves;
}

#ifdef SCREENSHOTS_ON
void check_capture_screen() {
  if (screenshot) {
    std::string path = "assets/screenshots/";
    path += str(board.screenshot_num);
    path += ".png";
    take_screenshot(window, path);
    screenshot = false;
    board.screenshot_num ++;
  }
}
#endif

void play() {
  #ifdef IS_BLACK_AI
  return;
  #endif
  if (queue.row.size() >= 2 && blocks[queue.row[0]][queue.col[0]] == 1 && blocks[queue.row[1]][queue.col[1]] == 0) {
    std::string piece = get_piece(queue.row[0], queue.col[0]);
    move_piece(piece, queue.row[1], queue.col[1]);
  }
  if (queue.row.size() >= 2) {
    std::vector<int> kingpos = {king.row, king.col};
    std::vector<int> k_rook = {rook.row[1], rook.col[1]};
    std::vector<int> q_rook = {rook.row[0], rook.col[0]};
    std::vector<int> queue0 = {queue.row[0], queue.col[0]};
    std::vector<int> queue1 = {queue.row[1], queue.col[1]};
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

void revive(std::string piece, int row, int col) {
  for (int i=0;i<num_queens;i++) {
    if (piece == "Q" + str(i)) {
      queen.pure_move(i, row, col);
      queen.alive[i] = 1;
    }
  }
  for (int i=0;i<8;i++) {
    if (piece == "P" + str(i)) {
      pawn.pure_move(i, row, col);
      pawn.alive[i] = 1;
    }
  }
  for (int i=0;i<2;i++) {
    if (piece == "B" + str(i)) {
      bishop.pure_move(i, row, col);
      bishop.alive[i] = 1;
    }
    if (piece == "N" + str(i)) {
      knight.pure_move(i, row, col);
      knight.alive[i] = 1;
    }
    if (piece == "R" + str(i)) {
      rook.pure_move(i, row, col);
      rook.alive[i] = 1;
    }
  }
}

void castle_K(bool is_undo) {
  undo.moved_from.push_back({king.row, king.col});
  king.move(0, 6);
  rook.move(1, 0, 5);
  valid_move(is_undo, false, "CK", 0, 5);
}

void castle_Q(bool is_undo) {
  undo.moved_from.push_back({king.row, king.col});
  king.move(0, 2);
  rook.move(0, 0, 3);
  valid_move(is_undo, false, "CQ", 0, 4);
}

bool castle_criteria_Q() {
  if (king.row != 0 || king.col != 4 || rook.row[0] != 0 || rook.col[1] != 0) return false;
  if (king.moved || rook.moved[0] || !rook.alive[0])
    return false;
  if (white::blocks[0][2] || white::blocks[0][3] || blocks[0][2] || blocks[0][3])
    return false;
  if (white::checker.size() >= 1)
    return false;
  if (in_opp_movelist(0, 2) || in_opp_movelist(0, 3))
    return false;
  return true;
}

bool castle_criteria_K() {
  if (king.row != 0 || king.col != 4 || rook.row[0] != 0 || rook.col[1] != 7) return false;
  if (king.moved || rook.moved[1] || !rook.alive[1])
    return false;
  if (white::blocks[0][5] || white::blocks[0][6] || blocks[0][5] || blocks[0][6])
    return false;
  if (white::checker.size() >= 1)
    return false;
  if (in_opp_movelist(0, 5) || in_opp_movelist(0, 6))
    return false;
  return true;
}

void move_piece(std::string piece, int row, int col) {
  assert(row >= 0 && row < 8 && col >= 0 && col < 8);
  std::vector<int> pos = {row, col};
  bool moved = false;
  checker.clear();
  bool killed = false;
  if (piece == "K" && in(king.movelist, pos)) {
    if (!board.isFrozen) reset_enpassant();
    undo.moved_from.push_back({king.row, king.col});
    king.move(row, col);
    moved = true;
  }
  else if (piece == "K" && !in(king.movelist, pos)) {
    sound.error();
    return;
  }
  for (int i=0;i<num_queens;i++) {
    if (piece == "Q" + std::to_string(i) && in(queen.movelist[i], pos)) {
      if (!board.isFrozen) reset_enpassant();
      undo.moved_from.push_back({queen.row[i], queen.col[i]});
      queen.move(i, row, col);
      moved = true;
    }
    else if (piece == "Q" + std::to_string(i) && !in(queen.movelist[i], pos)) {
      sound.error();
      return;
    }
  }
  for (int i=0;i<8;i++) {
    if (piece == "P" + std::to_string(i) && in(pawn.movelist[i], pos)) {
      if (!board.isFrozen) reset_enpassant();
      undo.moved_from.push_back({pawn.row[i], pawn.col[i]});
      if (pawn.row[i] == 4) {
        for (int k=0;k<8;k++) {
          if (white::en_passant[k]) {
            if (abs(pawn.col[i] - white::pawn.col[k]) == 1 && col == white::pawn.col[k]) {
              check_kill(false, 4, white::pawn.col[k]);
              enpassant_check_killed = true;
              killed = true;
            }
          }
        }
      }
      pawn.move(i, row, col);
      if (row == 7)
        promote(i, row, col);
      moved = true;
    }
    else if (piece == "P" + std::to_string(i) && !in(pawn.movelist[i], pos)) {
      sound.error();
      return;
    }
  }
  for (int i=0;i<2;i++) {
    if (piece == "B" + std::to_string(i) && in(bishop.movelist[i], pos)) {
      if (!board.isFrozen) reset_enpassant();
      undo.moved_from.push_back({bishop.row[i], bishop.col[i]});
      bishop.move(i, row, col);
      moved = true;
    }
    else if (piece == "B" + std::to_string(i) && !in(bishop.movelist[i], pos)) {
      sound.error();
      return;
    }
    if (piece == "N" + std::to_string(i) && in(knight.movelist[i], pos)) {
      if (!board.isFrozen) reset_enpassant();
      undo.moved_from.push_back({knight.row[i], knight.col[i]});
      knight.move(i, row, col);
      moved = true;
    }
    else if (piece == "N" + std::to_string(i) && !in(knight.movelist[i], pos)) {
      sound.error();
      return;
    }
    if (piece == "R" + std::to_string(i) && in(rook.movelist[i], pos)) {
      if (!board.isFrozen) reset_enpassant();
      undo.moved_from.push_back({rook.row[i], rook.col[i]});
      rook.move(i, row, col);
      moved = true;
    }
    else if (piece == "R" + std::to_string(i) && !in(rook.movelist[i], pos)) {
      sound.error();
      return;
    }
  }
  if (moved)
    valid_move(false, killed, piece, row, col);
}

void valid_move(bool is_undo, bool killed, std::string piece, int row, int col) {
  if (!killed && !is_undo && !board.isFrozen)
    sound.move();
  if (!is_undo) {
    board.total_moves ++;
    undo.piece.push_back(piece);
    undo.color.push_back("B");
  }
  if (!enpassant_check_killed)
    check_kill(is_undo, row, col);
  board.update_moves();
  check_pin();
  if (check_opp_checked() && !is_undo) {
    if (!board.isFrozen)
      sound.check();
    update_opp_movelists();
    if (opp_no_moves())
      board.checkmate = true;
  }
  if (opp_no_moves() && !is_undo)
    board.stalemate = true;
  #ifdef SCREENSHOTS_ON
  if (!board.isFrozen)
    screenshot = true;
  #endif
  #ifndef IS_TESTING
  turn = false;
  white::turn = true;
  #endif
  enpassant_check_killed = false;
}

void reset_enpassant() {
  for (int i=0;i<8;i++)
    en_passant[i] = 0;
}

std::string get_piece(int row, int col) {
  assert(row >= 0 && row < 8 && col >= 0 && col < 8);
  if (king.row == row && king.col == col)
    return "K";
  for (int i=0;i<num_queens;i++) {
    if (queen.row[i] == row && queen.col[i] == col)
      return "Q" + std::to_string(i);
  }
  for (int i=0;i<8;i++) {
    if (pawn.row[i] == row && pawn.col[i] == col)
      return "P" + std::to_string(i);
  }
  for (int i=0;i<2;i++) {
    if (bishop.row[i] == row && bishop.col[i] == col)
      return "B" + std::to_string(i);
    else if (knight.row[i] == row && knight.col[i] == col)
      return "N" + std::to_string(i);
    else if (rook.row[i] == row && rook.col[i] == col)
      return "R" + std::to_string(i);
  }
}

void print_blocks() {
  print("--black blocks--");
  for (int i=0;i<8;i++) {
    for (int k=0;k<8;k++)
      printf("%d", blocks[i][k]);
    printf("\n");
  }
}

#ifdef DEBUGAI
void print_blocks_Log() {
  Log << ("--black blocks--\n");
  for (int i=0;i<8;i++) {
    for (int k=0;k<8;k++)
      Log << blocks[i][k];
    Log << std::endl;
  }
}
#endif

void show() {
  bishop.show();
  knight.show();
  pawn.show();
  rook.show();
  king.show();
  queen.show();
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
  #ifdef IS_TESTING
  turn = true;
  #endif
}

void kill(bool is_undo, std::string piece, int row, int col) {
  blocks[row][col] = 0;
  if (piece == "K") {
    king.row = -1;
    king.col = -1;
    king.x = -1;
    king.y = -1;
    king.alive = false;
    king.movelist.clear();
  }
  for (int i=0;i<num_queens;i++) {
    if (piece == "Q" + std::to_string(i)) {
      queen.row[i] = -1;
      queen.col[i] = -1;
      queen.x[i] = -1;
      queen.y[i] = -1;
      queen.alive[i] = false;
      queen.movelist[i].clear();
      queen.protecting_movelist[i].clear();
    }
  }
  for (int i=0;i<8;i++) {
    if (piece == "P" + std::to_string(i)) {
      pawn.row[i] = -1;
      pawn.col[i] = -1;
      pawn.x[i] = -1;
      pawn.y[i] = -1;
      pawn.alive[i] = false;
      pawn.movelist[i].clear();
      pawn.hit_movelist[i].clear();
    }
  }
  for (int i=0;i<2;i++) {
    if (piece == "B" + std::to_string(i)) {
      bishop.row[i] = -1;
      bishop.col[i] = -1;
      bishop.x[i] = -1;
      bishop.y[i] = -1;
      bishop.alive[i] = false;
      bishop.movelist[i].clear();
      bishop.protecting_movelist[i].clear();
    }
    if (piece == "N" + std::to_string(i)) {
      knight.row[i] = -1;
      knight.col[i] = -1;
      knight.x[i] = -1;
      knight.y[i] = -1;
      knight.alive[i] = false;
      knight.movelist[i].clear();
      knight.protecting_movelist[i].clear();
    }
    if (piece == "R" + std::to_string(i)) {
      rook.row[i] = -1;
      rook.col[i] = -1;
      rook.x[i] = -1;
      rook.y[i] = -1;
      rook.alive[i] = false;
      rook.movelist[i].clear();
      rook.protecting_movelist[i].clear();
    }
  }
  if (!is_undo && !board.isFrozen)
    sound.kill();
}

} // namespace black
