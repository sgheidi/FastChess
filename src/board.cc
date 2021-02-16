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
    circle.setPosition(col*UNIT + 2*board.pieces_paddingx, row*UNIT + 3*board.pieces_paddingy);
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
      white::king.move(7, 4);
      white::rook.move(1, 7, 7);
      white::king.moved = 0;
      white::rook.moved[1] = 0;
    }
    else if (undo.piece[last] == "CQ") {
      castled = true;
      white::king.move(7, 4);
      white::rook.move(0, 7, 0);
      white::king.moved = 0;
      white::rook.moved[0] = 0;
    }
    else if (undo.piece[last] == "K")
      white::king.move(undo.moved_from[last][0], undo.moved_from[last][1]);
    for (int i=0;i<white::num_queens;i++) {
      if (undo.piece[last] == "Q" + std::to_string(i))
        white::queen.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
    }
    for (int i=0;i<8;i++) {
      if (undo.piece[last] == "P" + std::to_string(i)) {
        if (undo.moved_from[last][0] == 1)
          white::handle_undo_promotion(i, undo.moved_from[last][0], undo.moved_from[last][1]);
        white::pawn.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
      }
    }
    for (int i=0;i<2;i++) {
      if (undo.piece[last] == "B" + std::to_string(i))
        white::bishop.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
      else if (undo.piece[last] == "N" + std::to_string(i))
        white::knight.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
      else if (undo.piece[last] == "R" + std::to_string(i))
        white::rook.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
    }
    if (undo.killed[last] && undo.killed_color[last] == "B")
      black::revive(undo.killed_piece[last], undo.killed_pos[last][0], undo.killed_pos[last][1]);
    if (!board.isFrozen) white::reset_enpassant();
    white::valid_move(true, undo.killed[last], undo.piece[last], undo.moved_from[last][0], undo.moved_from[last][1]);
  }
  else if (undo.color[last] == "B") {
    if (undo.piece[last] == "CK") {
      castled = true;
      black::king.move(0, 4);
      black::rook.move(1, 0, 7);
      black::king.moved = 0;
      black::rook.moved[1] = 0;
    }
    else if (undo.piece[last] == "CQ") {
      castled = true;
      black::king.move(0, 4);
      black::rook.move(0, 0, 0);
      black::king.moved = 0;
      black::rook.moved[0] = 0;
    }
    if (undo.piece[last] == "K")
      black::king.move(undo.moved_from[last][0], undo.moved_from[last][1]);
    for (int i=0;i<black::num_queens;i++) {
      if (undo.piece[last] == "Q" + std::to_string(i))
        black::queen.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
    }
    for (int i=0;i<8;i++) {
      if (undo.piece[last] == "P" + std::to_string(i)) {
        if (undo.moved_from[last][0] == 6)
          black::handle_undo_promotion(i, undo.moved_from[last][0], undo.moved_from[last][1]);
        black::pawn.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
      }
    }
    for (int i=0;i<2;i++) {
      if (undo.piece[last] == "B" + std::to_string(i))
        black::bishop.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
      else if (undo.piece[last] == "N" + std::to_string(i))
        black::knight.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
      else if (undo.piece[last] == "R" + std::to_string(i))
        black::rook.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
    }
    if (undo.killed[last] && undo.killed_color[last] == "W")
      white::revive(undo.killed_piece[last], undo.killed_pos[last][0], undo.killed_pos[last][1]);
    if (!board.isFrozen)
      black::reset_enpassant();
    black::valid_move(true, undo.killed[last], undo.piece[last], undo.moved_from[last][0], undo.moved_from[last][1]);
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
  if (black::turn) {
    white::turn = true;
    black::turn = false;
  }
  else {
    white::turn = false;
    black::turn = true;
  }
  #ifdef IS_BLACK_AI
  white::turn = true;
  black::turn = false;
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
    text.checkmate();
  else if (stalemate)
    text.stalemate();
}

void Game_Board::update_moves() {
  white::pawn.update_movelist();
  white::queen.update_movelist();
  white::bishop.update_movelist();
  white::knight.update_movelist();
  white::rook.update_movelist();
  black::pawn.update_movelist();
  black::queen.update_movelist();
  black::bishop.update_movelist();
  black::knight.update_movelist();
  black::rook.update_movelist();
  white::king.update_movelist();
  black::king.update_movelist();
}

void Game_Board::play() {
  if (checkmate || stalemate)
    return;
  if (black::turn)
    black::play();
  else if (white::turn)
    white::play();
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
    for (int i=0;i<white::king.movelist.size();i++)
      Circle(white::king.movelist[i][0], white::king.movelist[i][1]);
  }
  for (int i=0;i<8;i++) {
    if (selected_piece == "P" + str(i)) {
      for (int k=0;k<white::pawn.movelist[i].size();k++)
        Circle(white::pawn.movelist[i][k][0], white::pawn.movelist[i][k][1]);
    }
  }
  for (int i=0;i<white::num_queens;i++) {
    if (selected_piece == "Q" + str(i)) {
      for (int k=0;k<white::queen.movelist[i].size();k++)
        Circle(white::queen.movelist[i][k][0], white::queen.movelist[i][k][1]);
    }
  }
  for (int i=0;i<2;i++) {
    if (selected_piece == "B" + str(i)) {
      for (int k=0;k<white::bishop.movelist[i].size();k++)
        Circle(white::bishop.movelist[i][k][0], white::bishop.movelist[i][k][1]);
    }
    else if (selected_piece == "N" + str(i)) {
      for (int k=0;k<white::knight.movelist[i].size();k++)
        Circle(white::knight.movelist[i][k][0], white::knight.movelist[i][k][1]);
    }
    else if (selected_piece == "R" + str(i)) {
      for (int k=0;k<white::rook.movelist[i].size();k++)
        Circle(white::rook.movelist[i][k][0], white::rook.movelist[i][k][1]);
    }
  }
}

std::string Game_Board::get_selected_piece() {
  if (clicked_piece != "") return clicked_piece;
  if (selected_row == -1 || selected_col == -1) return "";
  else if (!white::blocks[selected_row][selected_col]) return "";
  return white::get_piece(selected_row, selected_col);
}

// reset sprites to where they're supposed to be
void Game_Board::reset_pos() {
  white::king.move(white::king.row, white::king.col);
  for (int i=0;i<8;i++) {
    if (white::pawn.alive[i])
      white::pawn.move(i, white::pawn.row[i], white::pawn.col[i]);
  }
  for (int i=0;i<white::num_queens;i++) {
    if (white::queen.alive[i])
      white::queen.move(i, white::queen.row[i], white::queen.col[i]);
  }
  for (int i=0;i<2;i++) {
    if (white::bishop.alive[i])
      white::bishop.move(i, white::bishop.row[i], white::bishop.col[i]);
    if (white::rook.alive[i])
      white::rook.move(i, white::rook.row[i], white::rook.col[i]);
    if (white::knight.alive[i])
      white::knight.move(i, white::knight.row[i], white::knight.col[i]);
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
