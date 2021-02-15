#ifndef CORE_BLACK_KNIGHT_H
#define CORE_BLACK_KNIGHT_H

#include "../piece.h"

namespace Black {

class Knight_Piece : public Piece {
private:
public:
  Knight_Piece() {
    alive = {1, 1};
    movelist.resize(2);
    protecting_movelist.resize(2);
    row = {0, 0};
    col = {1, 6};
    y = {row[0]*UNIT, row[1]*UNIT};
    x = {col[0]*UNIT, col[1]*UNIT};
  };
  void move(int i, int row_, int col_);
  void pure_move(int i, int row_, int col_);
  void update_movelist();
  void show();
};

extern Knight_Piece knight;

} // namespace Black

#endif // CORE_BLACK_KNIGHT_H
