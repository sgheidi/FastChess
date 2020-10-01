#include "common.h"

void Game_Board::check_end() {
  if (checkmate)
    Text.checkmate();
  else if (stalemate)
    Text.stalemate();
}

void Game_Board::pop() {
  if (undo.color[total_moves-1] == "W") {
    for (int i=0;i<8;i++) {
      if (undo.piece[total_moves-1] == "P" + std::to_string(i)) {
        std::cout << "asd\n";
        White::Pawn.move(i, undo.moved_from[total_moves-1][0], undo.moved_from[total_moves-1][1]);
      }
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

void Game_Board::arrow(std::vector<int> start, std::vector<int> end) {

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
