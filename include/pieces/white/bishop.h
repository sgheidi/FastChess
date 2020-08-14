#ifndef WHITE_BISHOP_H
#define WHITE_BISHOP_H

namespace White {

class Bishop_Piece : public Piece {
private:
public:
  Bishop_Piece() {
    alive = true;
    movelist.resize(2);
    row = {7, 7};
    col = {2, 5};
    y = {row[0]*UNIT, row[1]*UNIT};
    x = {col[0]*UNIT, col[1]*UNIT};
  };
  void move(int i, int row_, int col_);
  void update_movelist();
  void show();
};

} // namespace White

#endif // WHITE_BISHOP_H
