#include "../../../include/common.h"

void Black_Knight::update_movelist() {

}


void Black_Knight::show() {
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
