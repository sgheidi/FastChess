#ifndef WHITE_KNIGHT_H
#define WHITE_KNIGHT_H

class White_Knight : public Piece {
private:
public:
  White_Knight() {
    row = {7, 7};
    col = {1, 6};
    x = {col[0]*UNIT, col[1]*UNIT};
    y = {row[0]*UNIT, row[1]*UNIT};
    alive = true;
  };
  void update_movelist();
  void move(int i, int row_, int col_);
  void show();
};

extern White_Knight WKnight;

#endif // WHITE_KNIGHT_H
