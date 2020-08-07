#include "../../../include/common.h"

void White_Rook::move(int i, int row_, int col_) {
  White.blocks[row[i]][col[i]] = 0;
  White.blocks[row_][col_] = 1;
  row[i] = row_;
  col[i] = col_;
  x[i] = col[i]*UNIT;
  y[i] = row[i]*UNIT;
}

void White_Rook::show() {
  for (int i=0;i<2;i++) {
    sf::Texture texture;
    if (!texture.loadFromFile("assets/sprites/whiteRook.png"))
      return;
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(Board.pieces_scale, Board.pieces_scale);
    sprite.setPosition(x[i] + Board.pieces_paddingx, y[i] + Board.pieces_paddingy);
    window.draw(sprite);
  }
}
