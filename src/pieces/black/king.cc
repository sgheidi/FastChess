#include "../../../include/common.h"

void Black_King::show() {
  sf::Texture texture;
  if (!texture.loadFromFile("assets/sprites/blackKing.png"))
    return;
  sf::Sprite sprite;
  sprite.setTexture(texture);
  sprite.setScale(Board.pieces_scale, Board.pieces_scale);
  sprite.setPosition(x + Board.pieces_paddingx, y + Board.pieces_paddingy);
  window.draw(sprite);
}
