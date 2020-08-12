#ifndef BLACK_BISHOP_H
#define BLACK_BISHOP_H

class Black_Bishop : public Piece {
private:
public:
  Black_Bishop() {
    alive = true;
    row = {0, 0};
    col = {2, 5};
    y = {row[0]*UNIT, row[1]*UNIT};
    x = {col[0]*UNIT, col[1]*UNIT};
  };
  void update_movelist();
  void show();
};

extern Black_Bishop BBishop;

#endif // BLACK_BISHOP_H
