#ifndef WHITE_KING_H
#define WHITE_KING_H

class White_King : public Piece {
private:
  int x, y;
public:
  std::vector<std::vector<int>> movelist;
  int row, col;
  White_King() {
    row = 7;
    col = 3;
    y = row*UNIT;
    x = col*UNIT;
    movelist = {};
    alive = true;
  };
  void update_movelist();
  void move(int row_, int col_);
  void show();
};

extern White_King WKing;

#endif // WHITE_KING_H
