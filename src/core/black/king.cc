#include "../../common.h"

namespace Black {

void King_Piece::update_movelist() {
  if (!alive)
    return;
  movelist.clear();
  std::vector<std::vector<int>> pos = {
  {row-1, col-1}, {row-1, col}, {row-1, col+1},
  {row, col-1}, {row, col}, {row, col+1},
  {row+1, col-1}, {row+1, col}, {row+1, col+1},
  };
  for (int k=0;k<pos.size();k++) {
    if (pos[k][0] >= 0 && pos[k][0] < 8 && pos[k][1] >= 0 && pos[k][1] < 8) {
      if (!blocks[pos[k][0]][pos[k][1]])
        movelist.push_back({pos[k][0], pos[k][1]});
    }
  }
  filter_king_pos();
  filter_check_pos();
}

void King_Piece::filter_check_pos() {
  for (int i=0;i<White::num_queens;i++) {
    movelist = filter2(movelist, White::Queen.movelist[i]);
    movelist = filter2(movelist, White::Queen.protecting_movelist[i]);
  }
  for (int i=0;i<8;i++) {
    movelist = filter2(movelist, White::Pawn.hit_movelist[i]);
  }
  for (int i=0;i<2;i++) {
    movelist = filter2(movelist, White::Bishop.movelist[i]);
    movelist = filter2(movelist, White::Bishop.protecting_movelist[i]);
    movelist = filter2(movelist, White::Knight.movelist[i]);
    movelist = filter2(movelist, White::Knight.protecting_movelist[i]);
    movelist = filter2(movelist, White::Rook.movelist[i]);
    movelist = filter2(movelist, White::Rook.protecting_movelist[i]);
  }
}

void King_Piece::filter_king_pos() {
  std::vector<std::vector<int>> opposite_pos = {
  {White::King.row-1, White::King.col-1}, {White::King.row-1, White::King.col},
  {White::King.row-1, White::King.col+1}, {White::King.row, White::King.col-1},
  {White::King.row, White::King.col}, {White::King.row, White::King.col+1},
  {White::King.row+1, White::King.col-1}, {White::King.row+1, White::King.col},
  {White::King.row+1, White::King.col+1}
  };
  movelist = filter2(movelist, opposite_pos);
}

void King_Piece::move(int row_, int col_) {
  moved = 1;
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
  if (!texture.loadFromFile("assets/sprites/blackKing.png"))
    return;
  sprite.setTexture(texture);
  sprite.setScale(Board.pieces_scale, Board.pieces_scale);
  sprite.setPosition(x + Board.pieces_paddingx, y + Board.pieces_paddingy);
  window.draw(sprite);
}

} // namespace Black
