#include "../../../include/common.h"

void Black_Queen::update_movelist() {

}


void Black_Queen::show() {
  sf::Texture texture;
  if (!texture.loadFromFile("assets/sprites/blackQueen.png"))
    return;
  sf::Sprite sprite;
  sprite.setTexture(texture);
  sprite.setScale(Board.pieces_scale, Board.pieces_scale);
  sprite.setPosition(x + Board.pieces_paddingx, y + Board.pieces_paddingy);
  window.draw(sprite);
}
