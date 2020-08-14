#ifndef WHITE_KNIGHT_H
#define WHITE_KNIGHT_H

namespace White {

class Knight_Piece : public Piece {
private:
public:
  Knight_Piece() {
    row = {7, 7};
    col = {1, 6};
    x = {col[0]*UNIT, col[1]*UNIT};
    y = {row[0]*UNIT, row[1]*UNIT};
    alive = true;
  };
  void move(int i, int row_, int col_);
  void update_movelist();
  void show();
};

} // namespace White

#endif // WHITE_KNIGHT_H
