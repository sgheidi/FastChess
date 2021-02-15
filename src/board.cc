#include <assert.h>

#include "common/config.h"
#include "common/util.h"

#include "board.h"
#include "core/piece.h"
#include "media/text.h"

#include "core/black/bishop.h"
#include "core/black/knight.h"
#include "core/black/pawn.h"
#include "core/black/rook.h"
#include "core/black/queen.h"
#include "core/black/king.h"

#include "core/white/bishop.h"
#include "core/white/knight.h"
#include "core/white/pawn.h"
#include "core/white/rook.h"
#include "core/white/queen.h"
#include "core/white/king.h"

#include "core/white_.h"
#include "core/black_.h"

namespace {
  // Draw a rectangle at (x, y) with 'width' and 'height'
  void drawRect(int*color, int x, int y, int width, int height) {
    sf::RectangleShape rectangle(sf::Vector2f(width, height));
    rectangle.setPosition(x, y);
    rectangle.setFillColor(sf::Color(color[0], color[1], color[2]));
    window.draw(rectangle);
  }

  void Circle(int row, int col) {
    sf::CircleShape circle(10);
    circle.setPosition(col*UNIT + 2*Board.pieces_paddingx, row*UNIT + 3*Board.pieces_paddingy);
    circle.setFillColor(sf::Color(110, 71, 55));
    window.draw(circle);
  }
} // namespace

void Game_Board::pop() {
  int last = total_moves-1;
  #ifdef VERBOSE2 
    std::cout << "Undoing " << undo.piece[last] << " " << undo.moved_from[last][0] << " " << undo.moved_from[last][1] << std::endl;
  #endif
  #ifdef DEBUGAI
    Log << "Undoing " << undo.piece[last] << " " << undo.moved_from[last][0] << " " << undo.moved_from[last][1] << std::endl;
  #endif
  if (last < 0)
    return;
  assert(last >= 0);
  bool castled = false;
  if (undo.color[last] == "W") {
    if (undo.piece[last] == "CK") {
      castled = true;
      White::king.move(7, 4);
      White::rook.move(1, 7, 7);
      White::king.moved = 0;
      White::rook.moved[1] = 0;
    }
    else if (undo.piece[last] == "CQ") {
      castled = true;
      White::king.move(7, 4);
      White::rook.move(0, 7, 0);
      White::king.moved = 0;
      White::rook.moved[0] = 0;
    }
    else if (undo.piece[last] == "K")
      White::king.move(undo.moved_from[last][0], undo.moved_from[last][1]);
    for (int i=0;i<White::num_queens;i++) {
      if (undo.piece[last] == "Q" + std::to_string(i))
        White::queen.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
    }
    for (int i=0;i<8;i++) {
      if (undo.piece[last] == "P" + std::to_string(i)) {
        if (undo.moved_from[last][0] == 1)
          White::handle_undo_promotion(i, undo.moved_from[last][0], undo.moved_from[last][1]);
        White::pawn.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
      }
    }
    for (int i=0;i<2;i++) {
      if (undo.piece[last] == "B" + std::to_string(i))
        White::bishop.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
      else if (undo.piece[last] == "N" + std::to_string(i))
        White::knight.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
      else if (undo.piece[last] == "R" + std::to_string(i))
        White::rook.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
    }
    if (undo.killed[last] && undo.killed_color[last] == "B")
      Black::revive(undo.killed_piece[last], undo.killed_pos[last][0], undo.killed_pos[last][1]);
    if (!Board.isFrozen) White::reset_enpassant();
    White::valid_move(true, undo.killed[last], undo.piece[last], undo.moved_from[last][0], undo.moved_from[last][1]);
  }
  else if (undo.color[last] == "B") {
    if (undo.piece[last] == "CK") {
      castled = true;
      Black::king.move(0, 4);
      Black::rook.move(1, 0, 7);
      Black::king.moved = 0;
      Black::rook.moved[1] = 0;
    }
    else if (undo.piece[last] == "CQ") {
      castled = true;
      Black::king.move(0, 4);
      Black::rook.move(0, 0, 0);
      Black::king.moved = 0;
      Black::rook.moved[0] = 0;
    }
    if (undo.piece[last] == "K")
      Black::king.move(undo.moved_from[last][0], undo.moved_from[last][1]);
    for (int i=0;i<Black::num_queens;i++) {
      if (undo.piece[last] == "Q" + std::to_string(i))
        Black::queen.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
    }
    for (int i=0;i<8;i++) {
      if (undo.piece[last] == "P" + std::to_string(i)) {
        if (undo.moved_from[last][0] == 6)
          Black::handle_undo_promotion(i, undo.moved_from[last][0], undo.moved_from[last][1]);
        Black::pawn.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
      }
    }
    for (int i=0;i<2;i++) {
      if (undo.piece[last] == "B" + std::to_string(i))
        Black::bishop.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
      else if (undo.piece[last] == "N" + std::to_string(i))
        Black::knight.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
      else if (undo.piece[last] == "R" + std::to_string(i))
        Black::rook.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
    }
    if (undo.killed[last] && undo.killed_color[last] == "W")
      White::revive(undo.killed_piece[last], undo.killed_pos[last][0], undo.killed_pos[last][1]);
    if (!Board.isFrozen)
      Black::reset_enpassant();
    Black::valid_move(true, undo.killed[last], undo.piece[last], undo.moved_from[last][0], undo.moved_from[last][1]);
  }
  checkmate = false;
  stalemate = false;
  total_moves --;
  undo.color.resize(total_moves);
  undo.killed.resize(total_moves);
  undo.piece.resize(total_moves);
  undo.moved_from.resize(total_moves);
  undo.killed_piece.resize(total_moves);
  undo.killed_pos.resize(total_moves);
  undo.killed_color.resize(total_moves);
  #ifdef IS_TESTING
  if (Black::turn) {
    White::turn = true;
    Black::turn = false;
  }
  else {
    White::turn = false;
    Black::turn = true;
  }
  #ifdef IS_BLACK_AI
  White::turn = true;
  Black::turn = false;
  #endif
  #endif
}

void Game_Board::print_undo() {
  print("----UNDO STACK----");
  print_v2(undo.moved_from);
  print_v1(undo.piece);
  print_v1(undo.color);
  print_v1(undo.killed);
  print_v1(undo.killed_piece);
  print_v2(undo.killed_pos);
  print_v1(undo.killed_color);
}

void Game_Board::check_end() {
  if (checkmate)
    Text.checkmate();
  else if (stalemate)
    Text.stalemate();
}

void Game_Board::update_moves() {
  White::pawn.update_movelist();
  White::queen.update_movelist();
  White::bishop.update_movelist();
  White::knight.update_movelist();
  White::rook.update_movelist();
  Black::pawn.update_movelist();
  Black::queen.update_movelist();
  Black::bishop.update_movelist();
  Black::knight.update_movelist();
  Black::rook.update_movelist();
  White::king.update_movelist();
  Black::king.update_movelist();
}

void Game_Board::play() {
  if (checkmate || stalemate)
    return;
  if (Black::turn)
    Black::play();
  else if (White::turn)
    White::play();
}

void Game_Board::draw_board() {
  int brown[3] = {92, 48, 17};
  int white[3] = {180, 180, 180};
  int x = 0;
  int y = 0;
  bool outer = true;
  for (int k=0; k<8; k++) {
    outer = !outer;
    for (int i=0; i<8; i++) {
      if (outer) {
        (i%2 == 0) ? drawRect(brown, x, y, UNIT, UNIT) : drawRect(white, x, y, UNIT, UNIT);
        x += UNIT;
      }
      else {
        (i%2 == 0) ? drawRect(white, x, y, UNIT, UNIT) : drawRect(brown, x, y, UNIT, UNIT);
        x += UNIT;
      }
    }
    y += UNIT;
    x = 0;
  }
}

// show legal moves of selected piece
void Game_Board::show_legal_moves() {
  const std::string selected_piece = get_selected_piece();
  if (selected_piece == "") return;
  else if (selected_piece == "K") {
    for (int i=0;i<White::king.movelist.size();i++)
      Circle(White::king.movelist[i][0], White::king.movelist[i][1]);
  }
  for (int i=0;i<8;i++) {
    if (selected_piece == "P" + str(i)) {
      for (int k=0;k<White::pawn.movelist[i].size();k++)
        Circle(White::pawn.movelist[i][k][0], White::pawn.movelist[i][k][1]);
    }
  }
  for (int i=0;i<White::num_queens;i++) {
    if (selected_piece == "Q" + str(i)) {
      for (int k=0;k<White::queen.movelist[i].size();k++)
        Circle(White::queen.movelist[i][k][0], White::queen.movelist[i][k][1]);
    }
  }
  for (int i=0;i<2;i++) {
    if (selected_piece == "B" + str(i)) {
      for (int k=0;k<White::bishop.movelist[i].size();k++)
        Circle(White::bishop.movelist[i][k][0], White::bishop.movelist[i][k][1]);
    }
    else if (selected_piece == "N" + str(i)) {
      for (int k=0;k<White::knight.movelist[i].size();k++)
        Circle(White::knight.movelist[i][k][0], White::knight.movelist[i][k][1]);
    }
    else if (selected_piece == "R" + str(i)) {
      for (int k=0;k<White::rook.movelist[i].size();k++)
        Circle(White::rook.movelist[i][k][0], White::rook.movelist[i][k][1]);
    }
  }
}

std::string Game_Board::get_selected_piece() {
  if (clicked_piece != "") return clicked_piece;
  if (selected_row == -1 || selected_col == -1) return "";
  else if (!White::blocks[selected_row][selected_col]) return "";
  return White::get_piece(selected_row, selected_col);
}

// reset sprites to where they're supposed to be
void Game_Board::reset_pos() {
  White::king.move(White::king.row, White::king.col);
  for (int i=0;i<8;i++) {
    if (White::pawn.alive[i])
      White::pawn.move(i, White::pawn.row[i], White::pawn.col[i]);
  }
  for (int i=0;i<White::num_queens;i++) {
    if (White::queen.alive[i])
      White::queen.move(i, White::queen.row[i], White::queen.col[i]);
  }
  for (int i=0;i<2;i++) {
    if (White::bishop.alive[i])
      White::bishop.move(i, White::bishop.row[i], White::bishop.col[i]);
    if (White::rook.alive[i])
      White::rook.move(i, White::rook.row[i], White::rook.col[i]);
    if (White::knight.alive[i])
      White::knight.move(i, White::knight.row[i], White::knight.col[i]);
  }
}

// Return (row, col) of pixel coords (x, y)
std::vector<int> Game_Board::get_coords(const int x, const int y) {
  if (x >= 0 && y >= 0 && x <= X_RES && y <= Y_RES)
    return {x/UNIT, y/UNIT};
}

// select (row, col) by clicking on the board
void Game_Board::select(const int row, const int col) {
  if (row < 0 || row > 7 || col > 7 || col < 0)
    return;
  int color[3] = {173, 199, 137};
  int x = col*UNIT;
  int y = row*UNIT;
  drawRect(color, x, y, UNIT, UNIT);
}
