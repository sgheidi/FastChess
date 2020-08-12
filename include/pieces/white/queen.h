#ifndef WHITE_QUEEN_H
#define WHITE_QUEEN_H

class White_Queen : public Piece {
private:
  int x, y;
public:
  int row, col;
  White_Queen() {
    row = 7;
    col = 4;
    y = row*UNIT;
    x = col*UNIT;
    alive = true;
  };
  void update_movelist();
  void move(int row_, int col_);
  void show();
};

extern White_Queen WQueen;

#endif // WHITE_QUEEN_H
