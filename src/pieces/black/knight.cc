#include "../../../include/common.h"

namespace Black {

void Knight_Piece::update_movelist() {

}


void Knight_Piece::show() {
  for (int i=0;i<2;i++) {
    sf::Texture texture;
    if (!texture.loadFromFile("assets/sprites/blackKnight.png"))
      return;
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(Board.pieces_scale, Board.pieces_scale);
    sprite.setPosition(x[i] + Board.pieces_paddingx, y[i] + Board.pieces_paddingy);
    window.draw(sprite);
  }
}

} // namespace Black
