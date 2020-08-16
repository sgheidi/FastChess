#include "../../../include/common.h"

namespace White {

void Queen_Piece::update_movelist() {
  for (int i=0;i<num_queens;i++) {
    if (!alive[i])
      continue;
    movelist[i].clear();
    int row_ = row[i]+1;
    int col_ = col[i]+1;
    while (row_ <= 7 && col_ <= 7) {
      if (blocks[row_][col_])
        break;
      movelist[i].push_back({row_, col_});
      if (Black::blocks[row_][col_])
        break;
      row_ ++;
      col_ ++;
    }
    row_ = row[i]-1;
    col_ = col[i]+1;
    while (row_ >= 0 && col_ <= 7) {
      if (blocks[row_][col_])
        break;
      movelist[i].push_back({row_, col_});
      if (Black::blocks[row_][col_])
        break;
      row_ --;
      col_ ++;
    }
    row_ = row[i]+1;
    col_ = col[i]-1;
    while (row_ <= 7 && col_ >= 0) {
      if (blocks[row_][col_])
        break;
      movelist[i].push_back({row_, col_});
      if (Black::blocks[row_][col_])
        break;
      row_ ++;
      col_ --;
    }
    row_ = row[i]-1;
    col_ = col[i]-1;
    while (row_ >= 0 && col_ >= 0) {
      if (blocks[row_][col_])
        break;
      movelist[i].push_back({row_, col_});
      if (Black::blocks[row_][col_])
        break;
      row_ --;
      col_ --;
    }
    row_ = row[i]-1;
    col_ = col[i];
    while (row_ >= 0) {
      if (blocks[row_][col_])
        break;
      movelist[i].push_back({row_, col_});
      if (Black::blocks[row_][col_])
        break;
      row_ --;
    }
    row_ = row[i]+1;
    col_ = col[i];
    while (row_ < 8) {
      if (blocks[row_][col_])
        break;
      movelist[i].push_back({row_, col_});
      if (Black::blocks[row_][col_])
        break;
      row_ ++;
    }
    row_ = row[i];
    col_ = col[i]+1;
    while (col_ < 8) {
      if (blocks[row_][col_])
        break;
      movelist[i].push_back({row_, col_});
      if (Black::blocks[row_][col_])
        break;
      col_ ++;
    }
    row_ = row[i];
    col_ = col[i]-1;
    while (col_ >= 0) {
      if (blocks[row_][col_])
        break;
      movelist[i].push_back({row_, col_});
      if (Black::blocks[row_][col_])
        break;
      col_ --;
    }
  }
}

void Queen_Piece::move(int i, int row_, int col_) {
  blocks[row[i]][col[i]] = 0;
  blocks[row_][col_] = 1;
  row[i] = row_;
  col[i] = col_;
  x[i] = col[i]*UNIT;
  y[i] = row[i]*UNIT;
}

void Queen_Piece::show() {
  for (int i=0;i<num_queens;i++) {
    if (!alive[i])
      continue;
    sf::Texture texture;
    if (!texture.loadFromFile("assets/sprites/whiteQueen.png"))
      return;
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(Board.pieces_scale, Board.pieces_scale);
    sprite.setPosition(x[i] + Board.pieces_paddingx, y[i] + Board.pieces_paddingy);
    window.draw(sprite);
  }
}

} // namespace White
