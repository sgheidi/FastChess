#include "../../../include/common.h"

namespace White {

void Queen_Piece::update_movelist() {
  movelist.clear();
  int row_ = row+1;
  int col_ = col+1;
  while (row_ <= 7 && col_ <= 7) {
    if (blocks[row_][col_])
      break;
    movelist.push_back({row_, col_});
    if (Black::blocks[row_][col_])
      break;
    row_ ++;
    col_ ++;
  }
  row_ = row-1;
  col_ = col+1;
  while (row_ >= 0 && col_ <= 7) {
    if (blocks[row_][col_])
      break;
    movelist.push_back({row_, col_});
    if (Black::blocks[row_][col_])
      break;
    row_ --;
    col_ ++;
  }
  row_ = row+1;
  col_ = col-1;
  while (row_ <= 7 && col_ >= 0) {
    if (blocks[row_][col_])
      break;
    movelist.push_back({row_, col_});
    if (Black::blocks[row_][col_])
      break;
    row_ ++;
    col_ --;
  }
  row_ = row-1;
  col_ = col-1;
  while (row_ >= 0 && col_ >= 0) {
    if (blocks[row_][col_])
      break;
    movelist.push_back({row_, col_});
    if (Black::blocks[row_][col_])
      break;
    row_ --;
    col_ --;
  }
  row_ = row-1;
  col_ = col;
  while (row_ >= 0) {
    if (blocks[row_][col_])
      break;
    movelist.push_back({row_, col_});
    if (Black::blocks[row_][col_])
      break;
    row_ --;
  }
  row_ = row+1;
  col_ = col;
  while (row_ < 8) {
    if (blocks[row_][col_])
      break;
    movelist.push_back({row_, col_});
    if (Black::blocks[row_][col_])
      break;
    row_ ++;
  }
  row_ = row;
  col_ = col+1;
  while (col_ < 8) {
    if (blocks[row_][col_])
      break;
    movelist.push_back({row_, col_});
    if (Black::blocks[row_][col_])
      break;
    col_ ++;
  }
  row_ = row;
  col_ = col-1;
  while (col_ >= 0) {
    if (blocks[row_][col_])
      break;
    movelist.push_back({row_, col_});
    if (Black::blocks[row_][col_])
      break;
    col_ --;
  }
}

void Queen_Piece::move(int row_, int col_) {
  blocks[row][col] = 0;
  blocks[row_][col_] = 1;
  row = row_;
  col = col_;
  x = col*UNIT;
  y = row*UNIT;
}

void Queen_Piece::show() {
  if (!alive)
    return;
  sf::Texture texture;
  if (!texture.loadFromFile("assets/sprites/whiteQueen.png"))
    return;
  sf::Sprite sprite;
  sprite.setTexture(texture);
  sprite.setScale(Board.pieces_scale, Board.pieces_scale);
  sprite.setPosition(x + Board.pieces_paddingx, y + Board.pieces_paddingy);
  window.draw(sprite);
}

} // namespace White
