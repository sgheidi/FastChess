#ifndef BLACK_ROOK_H
#define BLACK_ROOK_H

namespace Black {

class Rook_Piece : public Piece {
private:
public:
  Rook_Piece() {
    alive = {1, 1};
    movelist.resize(2);
    row = {0, 0};
    col = {0, 7};
    y = {row[0]*UNIT, row[1]*UNIT};
    x = {col[0]*UNIT, col[1]*UNIT};
  };
  void move(int i, int row_, int col_);
  void update_movelist();
  void show();
};

} // namespace Black

#endif // BLACK_ROOK_H
