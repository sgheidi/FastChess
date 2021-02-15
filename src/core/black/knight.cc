#include "../../common/config.h"

#include "../../board.h"

#include "knight.h"

#include "../black_.h"

namespace Black {

void Knight_Piece::pure_move(int i, int row_, int col_) {
  blocks[row_][col_] = 1;
  row[i] = row_;
  col[i] = col_;
  x[i] = col[i]*UNIT;
  y[i] = row[i]*UNIT;
}

void Knight_Piece::update_movelist() {
  for (int i=0;i<2;i++) {
    if (!alive[i]) continue;
    movelist[i].clear();
    protecting_movelist[i].clear();
    std::vector<std::vector<int>> pos = {{row[i]-2, col[i]+1}, {row[i]-2, col[i]-1},
    {row[i]+2, col[i]+1}, {row[i]+2, col[i]-1}, {row[i]-1, col[i]-2}, {row[i]-1, col[i]+2},
    {row[i]+1, col[i]-2}, {row[i]+1, col[i]+2}};
    for (int k=0;k<8;k++) {
      if (pos[k][0] >= 0 && pos[k][0] < 8 && pos[k][1] >= 0 && pos[k][1] < 8) {
        if (!blocks[pos[k][0]][pos[k][1]])
          movelist[i].push_back({pos[k][0], pos[k][1]});
        else if (blocks[pos[k][0]][pos[k][1]])
          protecting_movelist[i].push_back({pos[k][0], pos[k][1]});
      }
    }
  }
}

void Knight_Piece::move(int i, int row_, int col_) {
  blocks[row[i]][col[i]] = 0;
  blocks[row_][col_] = 1;
  row[i] = row_;
  col[i] = col_;
  x[i] = col[i]*UNIT;
  y[i] = row[i]*UNIT;
}

void Knight_Piece::show() {
  for (int i=0;i<2;i++) {
    if (!alive[i])
      continue;
    if (!texture.loadFromFile("assets/sprites/blackknight.png"))
      return;
    sprite.setTexture(texture);
    sprite.setScale(board.pieces_scale, board.pieces_scale);
    sprite.setPosition(x[i] + board.pieces_paddingx, y[i] + board.pieces_paddingy);
    window.draw(sprite);
  }
}

} // namespace Black
