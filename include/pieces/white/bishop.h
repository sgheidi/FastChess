#ifndef WHITE_BISHOP_H
#define WHITE_BISHOP_H

class White_Bishop : public Piece {
private:
public:
  White_Bishop() {
    alive = true;
    movelist.resize(2);
    row = {7, 7};
    col = {2, 5};
    y = {row[0]*UNIT, row[1]*UNIT};
    x = {col[0]*UNIT, col[1]*UNIT};
  };
  void update_movelist();
  void move(int i, int row_, int col_);
  void show();
};

extern White_Bishop WBishop;

#endif // WHITE_BISHOP_H
