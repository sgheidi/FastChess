#include "../../../include/common.h"

namespace Black {

void King_Piece::update_movelist() {

}


void King_Piece::show() {
  sf::Texture texture;
  if (!texture.loadFromFile("assets/sprites/blackKing.png"))
    return;
  sf::Sprite sprite;
  sprite.setTexture(texture);
  sprite.setScale(Board.pieces_scale, Board.pieces_scale);
  sprite.setPosition(x + Board.pieces_paddingx, y + Board.pieces_paddingy);
  window.draw(sprite);
}

} // namespace Black
