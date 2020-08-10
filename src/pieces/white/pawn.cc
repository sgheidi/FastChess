#include "../../../include/common.h"

void White_Pawn::update_movelist() {
  for (int i=0;i<8;i++) {
    if (!movelist[i].empty())
      movelist[i].erase(movelist[i].begin());
    if (row[i] > 0 && Black.blocks[row[i]-1][col[i]] == 0 && White.blocks[row[i]-1][col[i]] == 0) {
      movelist[i].push_back({row[i]-1, col[i]});
      if (row[i] == 6)
        movelist[i].push_back({row[i]-2, col[i]});
    // if ()
    }
  }
}

void White_Pawn::move(int i, int row_, int col_) {
  White.blocks[row[i]][col[i]] = 0;
  White.blocks[row_][col_] = 1;
  row[i] = row_;
  col[i] = col_;
  x[i] = col[i]*UNIT;
  y[i] = row[i]*UNIT;
}

void White_Pawn::show() {
  for (int i=0;i<8;i++) {
    sf::Texture texture;
    if (!texture.loadFromFile("assets/sprites/whitePawn.png"))
      return;
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(Board.pieces_scale, Board.pieces_scale);
    sprite.setPosition(x[i] + Board.pieces_paddingx, y[i] + Board.pieces_paddingy);
    window.draw(sprite);
  }
}
