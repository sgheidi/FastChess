#include "../../common/config.h"
#include "../../common/util.h"
#include "../../board.h"
#include "../black/bishop.h"
#include "../black/knight.h"
#include "../black/pawn.h"
#include "../black/rook.h"
#include "../black/queen.h"
#include "../black/king.h"
#include "king.h"
#include "../white_.h"
#include "../black_.h"

namespace white {

void King_Piece::update_movelist() {
  if (!alive) return;
  movelist.clear();
  const std::vector<std::vector<int>> pos = {
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
  for (int i=0;i<black::num_queens;i++) {
    filter2(movelist, black::queen.movelist[i]);
    filter2(movelist, black::queen.protecting_movelist[i]);
  }
  for (int i=0;i<8;i++) {
    filter2(movelist, black::pawn.hit_movelist[i]);
  }
  for (int i=0;i<2;i++) {
    filter2(movelist, black::bishop.movelist[i]);
    filter2(movelist, black::bishop.protecting_movelist[i]);
    filter2(movelist, black::knight.movelist[i]);
    filter2(movelist, black::knight.protecting_movelist[i]);
    filter2(movelist, black::rook.movelist[i]);
    filter2(movelist, black::rook.protecting_movelist[i]);
  }
}

void King_Piece::filter_king_pos() {
  const std::vector<std::vector<int>> opposite_pos = {
    {black::king.row-1, black::king.col-1}, {black::king.row-1, black::king.col},
    {black::king.row-1, black::king.col+1}, {black::king.row, black::king.col-1},
    {black::king.row, black::king.col}, {black::king.row, black::king.col+1},
    {black::king.row+1, black::king.col-1}, {black::king.row+1, black::king.col},
    {black::king.row+1, black::king.col+1}
    };
  filter2(movelist, opposite_pos);
}

void King_Piece::move(int row_, int col_) {
  moved = true;
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
  if (!texture.loadFromFile("assets/sprites/whiteking.png"))
    return;
  sprite.setTexture(texture);
  sprite.setScale(board.pieces_scale, board.pieces_scale);
  sprite.setPosition(x + board.pieces_paddingx, y + board.pieces_paddingy);
  window.draw(sprite);
}

} // namespace white
