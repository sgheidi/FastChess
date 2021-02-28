#ifndef CORE_WHITE_KING_H
#define CORE_WHITE_KING_H

#include "../piece.h"

namespace white {

class King_Piece : public Piece {
private:
  void filter_king_pos();
  void filter_check_pos();
public:
  bool moved;
  std::vector<std::vector<int>> movelist, protecting_movelist;
  int row, col, y, x;
  bool alive;
  King_Piece() {
    moved = 0;
    alive = true;
    row = 7;
    col = 4;
    y = row*UNIT;
    x = col*UNIT;
  };
  void update_movelist();
  void move(int row_, int col_);
  void show();
};

extern King_Piece king;

} // namespace white

#endif // CORE_WHITE_KING_H
