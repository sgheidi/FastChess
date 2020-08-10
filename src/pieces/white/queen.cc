#include "../../../include/common.h"

void White_Queen::update_movelist() {

}


void White_Queen::move(int row_, int col_) {
  White.blocks[row][col] = 0;
  White.blocks[row_][col_] = 1;
  row = row_;
  col = col_;
  x = col*UNIT;
  y = row*UNIT;
}

void White_Queen::show() {
  sf::Texture texture;
  if (!texture.loadFromFile("assets/sprites/whiteQueen.png"))
    return;
  sf::Sprite sprite;
  sprite.setTexture(texture);
  sprite.setScale(Board.pieces_scale, Board.pieces_scale);
  sprite.setPosition(x + Board.pieces_paddingx, y + Board.pieces_paddingy);
  window.draw(sprite);
}
