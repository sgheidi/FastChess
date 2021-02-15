#ifndef CORE_BLACK_KING_H
#define CORE_BLACK_KING_H

#include "../piece.h"

namespace Black {

class King_Piece : public Piece {
private:
  void filter_king_pos();
  void filter_check_pos();
public:
  bool moved;
  std::vector<std::vector<int>> movelist, protecting_movelist;
  int x, y, row, col;
  bool alive;
  King_Piece() {
    moved = 0;
    alive = true;
    row = 0;
    col = 4;
    y = row*UNIT;
    x = col*UNIT;
  };
  void move(int row_, int col_);
  void update_movelist();
  void show();
};

extern King_Piece king;

} // namespace Black

#endif // CORE_BLACK_KING_H
