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

void Game_Board::pop() {
  int last = total_moves-1;
  if (verbose2) std::cout << "Undoing " << undo.piece[last] << " " << undo.moved_from[last][0] << " "
  << undo.moved_from[last][1] << std::endl;
  #ifdef DEBUGAI
  Log << "Undoing " << undo.piece[last] << " " << undo.moved_from[last][0] << " "
  << undo.moved_from[last][1] << std::endl;
  #endif
  if (last < 0)
    return;
  assert(last >= 0);
  bool castled = false;
  if (undo.color[last] == "W") {
    if (undo.piece[last] == "CK") {
      castled = true;
      White::King.move(7, 4);
      White::Rook.move(1, 7, 7);
      White::King.moved = 0;
      White::Rook.moved[1] = 0;
    }
    else if (undo.piece[last] == "CQ") {
      castled = true;
      White::King.move(7, 4);
      White::Rook.move(0, 7, 0);
      White::King.moved = 0;
      White::Rook.moved[0] = 0;
    }
    else if (undo.piece[last] == "K")
      White::King.move(undo.moved_from[last][0], undo.moved_from[last][1]);
    for (int i=0;i<White::num_queens;i++) {
      if (undo.piece[last] == "Q" + std::to_string(i))
        White::Queen.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
    }
    for (int i=0;i<8;i++) {
      if (undo.piece[last] == "P" + std::to_string(i)) {
        if (undo.moved_from[last][0] == 1)
          White::handle_undo_promotion(i, undo.moved_from[last][0], undo.moved_from[last][1]);
        White::Pawn.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
      }
    }
    for (int i=0;i<2;i++) {
      if (undo.piece[last] == "B" + std::to_string(i))
        White::Bishop.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
      else if (undo.piece[last] == "N" + std::to_string(i))
        White::Knight.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
      else if (undo.piece[last] == "R" + std::to_string(i))
        White::Rook.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
    }
    if (undo.killed[last] && undo.killed_color[last] == "B")
      Black::revive(undo.killed_piece[last], undo.killed_pos[last][0], undo.killed_pos[last][1]);
    if (!Board.freeze) White::reset_enpassant();
    White::valid_move(true, undo.killed[last], undo.piece[last], undo.moved_from[last][0], undo.moved_from[last][1]);
  }
  else if (undo.color[last] == "B") {
    if (undo.piece[last] == "CK") {
      castled = true;
      Black::King.move(0, 4);
      Black::Rook.move(1, 0, 7);
      Black::King.moved = 0;
      Black::Rook.moved[1] = 0;
    }
    else if (undo.piece[last] == "CQ") {
      castled = true;
      Black::King.move(0, 4);
      Black::Rook.move(0, 0, 0);
      Black::King.moved = 0;
      Black::Rook.moved[0] = 0;
    }
    if (undo.piece[last] == "K")
      Black::King.move(undo.moved_from[last][0], undo.moved_from[last][1]);
    for (int i=0;i<Black::num_queens;i++) {
      if (undo.piece[last] == "Q" + std::to_string(i))
        Black::Queen.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
    }
    for (int i=0;i<8;i++) {
      if (undo.piece[last] == "P" + std::to_string(i)) {
        if (undo.moved_from[last][0] == 6)
          Black::handle_undo_promotion(i, undo.moved_from[last][0], undo.moved_from[last][1]);
        Black::Pawn.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
      }
    }
    for (int i=0;i<2;i++) {
      if (undo.piece[last] == "B" + std::to_string(i))
        Black::Bishop.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
      else if (undo.piece[last] == "N" + std::to_string(i))
        Black::Knight.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
      else if (undo.piece[last] == "R" + std::to_string(i))
        Black::Rook.move(i, undo.moved_from[last][0], undo.moved_from[last][1]);
    }
    if (undo.killed[last] && undo.killed_color[last] == "W")
      White::revive(undo.killed_piece[last], undo.killed_pos[last][0], undo.killed_pos[last][1]);
    if (!Board.freeze)
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
  if (!testing) {
    if (Black::turn) {
      White::turn = true;
      Black::turn = false;
    }
    else {
      White::turn = false;
      Black::turn = true;
    }
    if (isBlackAI) {
      White::turn = true;
      Black::turn = false;
    }
  }
}

void Game_Board::print_undo() {
  print("UNDO STACK");
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
  White::Pawn.update_movelist();
  White::Queen.update_movelist();
  White::Bishop.update_movelist();
  White::Knight.update_movelist();
  White::Rook.update_movelist();
  Black::Pawn.update_movelist();
  Black::Queen.update_movelist();
  Black::Bishop.update_movelist();
  Black::Knight.update_movelist();
  Black::Rook.update_movelist();
  White::King.update_movelist();
  Black::King.update_movelist();
}

void Game_Board::play() {
  if (checkmate || stalemate)
    return;
  if (Black::turn)
    Black::play();
  if (White::turn)
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
        if (i%2 == 0)
          drawRect(brown, x, y, UNIT, UNIT);
        else
          drawRect(white, x, y, UNIT, UNIT);
        x += UNIT;
      }
      else {
        if (i%2 == 0)
          drawRect(white, x, y, UNIT, UNIT);
        else
          drawRect(brown, x, y, UNIT, UNIT);
        x += UNIT;
      }
    }
    y += UNIT;
    x = 0;
  }
}

// Draw a rectangle at (x, y) with 'width' and 'height'
void Game_Board::drawRect(int*color, int x, int y, int width, int height) {
  sf::RectangleShape rectangle(sf::Vector2f(width, height));
  rectangle.setPosition(x, y);
  rectangle.setFillColor(sf::Color(color[0], color[1], color[2]));
  window.draw(rectangle);
}

void Game_Board::Circle(int row, int col) {
  sf::CircleShape circle(10);
  circle.setPosition(col*UNIT + 2*pieces_paddingx, row*UNIT + 3*pieces_paddingy);
  circle.setFillColor(sf::Color(110, 71, 55));
  window.draw(circle);
}

// show legal moves of selected piece
void Game_Board::show_legal_moves() {
  std::string selected_piece = get_selected_piece();
  if (selected_piece == "") return;
  else if (selected_piece == "K") {
    for (int i=0;i<White::King.movelist.size();i++)
      Circle(White::King.movelist[i][0], White::King.movelist[i][1]);
  }
  for (int i=0;i<8;i++) {
    if (selected_piece == "P" + str(i)) {
      for (int k=0;k<White::Pawn.movelist[i].size();k++)
        Circle(White::Pawn.movelist[i][k][0], White::Pawn.movelist[i][k][1]);
    }
  }
  for (int i=0;i<White::num_queens;i++) {
    if (selected_piece == "Q" + str(i)) {
      for (int k=0;k<White::Queen.movelist[i].size();k++)
        Circle(White::Queen.movelist[i][k][0], White::Queen.movelist[i][k][1]);
    }
  }
  for (int i=0;i<2;i++) {
    if (selected_piece == "B" + str(i)) {
      for (int k=0;k<White::Bishop.movelist[i].size();k++)
        Circle(White::Bishop.movelist[i][k][0], White::Bishop.movelist[i][k][1]);
    }
    else if (selected_piece == "N" + str(i)) {
      for (int k=0;k<White::Knight.movelist[i].size();k++)
        Circle(White::Knight.movelist[i][k][0], White::Knight.movelist[i][k][1]);
    }
    else if (selected_piece == "R" + str(i)) {
      for (int k=0;k<White::Rook.movelist[i].size();k++)
        Circle(White::Rook.movelist[i][k][0], White::Rook.movelist[i][k][1]);
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
  White::King.move(White::King.row, White::King.col);
  for (int i=0;i<8;i++) {
    if (White::Pawn.alive[i])
      White::Pawn.move(i, White::Pawn.row[i], White::Pawn.col[i]);
  }
  for (int i=0;i<White::num_queens;i++) {
    if (White::Queen.alive[i])
      White::Queen.move(i, White::Queen.row[i], White::Queen.col[i]);
  }
  for (int i=0;i<2;i++) {
    if (White::Bishop.alive[i])
      White::Bishop.move(i, White::Bishop.row[i], White::Bishop.col[i]);
    if (White::Rook.alive[i])
      White::Rook.move(i, White::Rook.row[i], White::Rook.col[i]);
    if (White::Knight.alive[i])
      White::Knight.move(i, White::Knight.row[i], White::Knight.col[i]);
  }
}

// Return (row, col) of pixel values
std::vector<int> Game_Board::get_coords(int x, int y) {
  if (x >= 0 && y >= 0 && x <= X_RES && y <= Y_RES)
    return {x/UNIT, y/UNIT};
}

// select (row, col) by clicking on the board
void Game_Board::select(int row, int col) {
  if (row < 0 || row > 7 || col > 7 || col < 0)
    return;
  int color[3] = {173, 199, 137};
  int x = col*UNIT;
  int y = row*UNIT;
  drawRect(color, x, y, UNIT, UNIT);
}
