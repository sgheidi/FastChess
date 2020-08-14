#ifndef WHITE_ROOK_H
#define WHITE_ROOK_H

namespace White {

class Rook_Piece : public Piece {
private:
public:
  Rook_Piece() {
    row = {7, 7};
    col = {0, 7};
    y = {row[0]*UNIT, row[1]*UNIT};
    x = {col[0]*UNIT, col[1]*UNIT};
    alive = true;
  };
  void move(int i, int row_, int col_);
  void update_movelist();
  void show();
};

} // namespace White

#endif // WHITE_ROOK_H
