#ifndef BLACK_ROOK_H
#define BLACK_ROOK_H

namespace Black {

class Rook_Piece : public Piece {
private:
public:
  Rook_Piece() {
    alive = {1, 1};
    row = {0, 0};
    col = {0, 7};
    y = {row[0]*UNIT, row[1]*UNIT};
    x = {col[0]*UNIT, col[1]*UNIT};
  };
  void update_movelist();
  void show();
};

} // namespace Black

#endif // BLACK_ROOK_H
