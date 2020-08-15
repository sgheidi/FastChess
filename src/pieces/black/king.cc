#include "../../../include/common.h"

namespace Black {

void King_Piece::update_movelist() {
  movelist.clear();
  std::vector<std::vector<int>> pos = {
  {row-1, col-1}, {row-1, col}, {row-1, col+1},
  {row, col-1}, {row, col}, {row, col+1},
  {row+1, col-1}, {row+1, col}, {row+1, col+1},
  };
  for (int k=0;k<9;k++) {
    if (pos[k][0] >= 0 && pos[k][0] < 8 && pos[k][1] >= 0 && pos[k][1] < 8) {
      if (!blocks[pos[k][0]][pos[k][1]])
        movelist.push_back({pos[k][0], pos[k][1]});
    }
  }
  filter_king_pos();
  // filter_check_pos();
}

void King_Piece::filter_king_pos() {
  std::vector<std::vector<int>> opposite_pos = {
  {Black::King.row-1, Black::King.col-1}, {Black::King.row-1, Black::King.col},
  {Black::King.row-1, Black::King.col+1}, {Black::King.row, Black::King.col-1},
  {Black::King.row, Black::King.col}, {Black::King.row, Black::King.col+1},
  {Black::King.row+1, Black::King.col-1}, {Black::King.row+1, Black::King.col},
  {Black::King.row+1, Black::King.col+1}
  };
}

void King_Piece::move(int row_, int col_) {
  blocks[row][col] = 0;
  blocks[row_][col_] = 1;
  row = row_;
  col = col_;
  x = col*UNIT;
  y = row*UNIT;
}

void King_Piece::show() {
  if (!alive)
    return;
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
