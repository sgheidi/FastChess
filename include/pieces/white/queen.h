#ifndef WHITE_QUEEN_H
#define WHITE_QUEEN_H

class White_Queen {
private:
public:
  int row = 7;
  int col = 4;
  int y = row*UNIT;
  int x = col*UNIT;
  White_Queen() {};
  void move(int row_, int col_);
  void show();
};

extern White_Queen WQueen;

#endif // WHITE_QUEEN_H
