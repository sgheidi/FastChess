#ifndef WHITE_ROOK_H
#define WHITE_ROOK_H

class White_Rook : public Piece {
private:
public:
  White_Rook() {
    row = {7, 7};
    col = {0, 7};
    y = {row[0]*UNIT, row[1]*UNIT};
    x = {col[0]*UNIT, col[1]*UNIT};
    alive = true;
  };
  void update_movelist();
  void move(int i, int row_, int col_);
  void show();
};

extern White_Rook WRook;

#endif // WHITE_ROOK_H
