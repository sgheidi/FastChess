#ifndef CORE_BLACK_PAWN_H
#define CORE_BLACK_PAWN_H

#include "../piece.h"

namespace black {

class Pawn_Piece : public Piece {
private:
public:
  Pawn_Piece() {
    for (int i=0;i<8;i++) {
      row.push_back(1);
      col.push_back(i);
      y.push_back(row[i]*UNIT);
      x.push_back(col[i]*UNIT);
      alive.push_back(1);
    }
    movelist.resize(8);
    hit_movelist.resize(8);
  };
  void move(int i, int row_, int col_);
  void pure_move(int i, int row_, int col_);
  void update_movelist();
  void show();
};

extern Pawn_Piece pawn;

} // namespace black

#endif // CORE_BLACK_PAWN_H
