#ifndef BLACK_QUEEN_H
#define BLACK_QUEEN_H

class Black_Queen {
private:
public:
  bool alive = true;
  int row = 0;
  int col = 4;
  int y = row*UNIT;
  int x = col*UNIT;
  Black_Queen() {};
  void update_movelist();
  void show();
};

extern Black_Queen BQueen;

#endif // BLACK_QUEEN_H
