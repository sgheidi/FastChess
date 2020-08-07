#ifndef WHITE_KING_H
#define WHITE_KING_H

class White_King {
private:
public:
  int row = 7;
  int col = 3;
  int y = row*UNIT;
  int x = col*UNIT;
  White_King() {};
  void move(int row_, int col_);
  void show();
};

extern White_King WKing;

#endif // WHITE_KING_H
