#ifndef BLACK_KING_H
#define BLACK_KING_H

class Black_King : public Piece {
private:
  int x, y;
public:
  int row, col;
  Black_King() {
    alive = true;
    row = 0;
    col = 3;
    y = row*UNIT;
    x = col*UNIT;
  };
  void update_movelist();
  void show();
};

extern Black_King BKing;

#endif // BLACK_KING_H
