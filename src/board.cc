#include "common.h"

void Game_Board::check_end() {
  if (checkmate)
    Text.checkmate();
  else if (stalemate)
    Text.stalemate();
}

void Game_Board::pop() {
  int last = total_moves-1;
  if (verbose) std::cout << "Undoing " << undo.piece[last] << " " << undo.moved_from[last][0] << " "
  << undo.moved_from[last][1] << std::endl;
  #ifdef DEBUGAI
  Log << "Undoing " << undo.piece[last] << " " << undo.moved_from[last][0] << " "
  << undo.moved_from[last][1] << std::endl;
  #endif
  if (last < 0)
    return
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
  if (castled)
    undo.color.resize(total_moves-1);
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

// Draw a rectangle at (x, y) with 'width' and 'height'
void Game_Board::drawRect(int*color, int x, int y, int width, int height) {
  sf::RectangleShape rectangle(sf::Vector2f(width, height));
  rectangle.setPosition(x, y);
  rectangle.setFillColor(sf::Color(color[0], color[1], color[2]));
  window.draw(rectangle);
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
          drawRect(white, x, y, UNIT, UNIT);
        else
          drawRect(brown, x, y, UNIT, UNIT);
        x += UNIT;
      }
      else {
        if (i%2 == 0)
          drawRect(brown, x, y, UNIT, UNIT);
        else
          drawRect(white, x, y, UNIT, UNIT);
        x += UNIT;
      }
    }
    y += UNIT;
    x = 0;
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
