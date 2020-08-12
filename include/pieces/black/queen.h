#ifndef BLACK_QUEEN_H
#define BLACK_QUEEN_H

class Black_Queen : public Piece {
private:
  int x, y;
public:
  int row, col;
  Black_Queen() {
    alive = true;
    row = 0;
    col = 4;
    y = row*UNIT;
    x = col*UNIT;
  };
  void update_movelist();
  void show();
};

extern Black_Queen BQueen;

#endif // BLACK_QUEEN_H
