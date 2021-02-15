#ifndef CORE_WHITE_KNIGHT_H
#define CORE_WHITE_KNIGHT_H

#include "../piece.h"

namespace White {

class Knight_Piece : public Piece {
private:
public:
  Knight_Piece() {
    alive = {1, 1};
    movelist.resize(2);
    protecting_movelist.resize(2);
    row = {7, 7};
    col = {1, 6};
    x = {col[0]*UNIT, col[1]*UNIT};
    y = {row[0]*UNIT, row[1]*UNIT};
  };
  void pure_move(int i, int row_, int col_);
  void move(int i, int row_, int col_);
  void update_movelist();
  void show();
};

extern Knight_Piece knight;

} // namespace White

#endif // CORE_WHITE_KNIGHT_H
