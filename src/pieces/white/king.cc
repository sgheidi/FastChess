#include "../../../include/common.h"

namespace White {

void King_Piece::update_movelist() {
  movelist.clear();
}

void King_Piece::move(int row_, int col_) {
  blocks[row][col] = 0;
  blocks[row_][col_] = 1;
  row = row_;
  col = col_;
  x = col*UNIT;
  y = row*UNIT;
}

void King_Piece::show() {
  sf::Texture texture;
  if (!texture.loadFromFile("assets/sprites/whiteKing.png"))
    return;
  sf::Sprite sprite;
  sprite.setTexture(texture);
  sprite.setScale(Board.pieces_scale, Board.pieces_scale);
  sprite.setPosition(x + Board.pieces_paddingx, y + Board.pieces_paddingy);
  window.draw(sprite);
}

} // namespace White
