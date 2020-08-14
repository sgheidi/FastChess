#include "../../../include/common.h"

namespace Black {

void Queen_Piece::update_movelist() {

}


void Queen_Piece::show() {
  sf::Texture texture;
  if (!texture.loadFromFile("assets/sprites/blackQueen.png"))
    return;
  sf::Sprite sprite;
  sprite.setTexture(texture);
  sprite.setScale(Board.pieces_scale, Board.pieces_scale);
  sprite.setPosition(x + Board.pieces_paddingx, y + Board.pieces_paddingy);
  window.draw(sprite);
}

} // namespace Black
