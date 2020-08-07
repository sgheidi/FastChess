#ifndef BLACK_KING_H
#define BLACK_KING_H

class Black_King {
private:
public:
  int row = 0;
  int col = 3;
  int y = row*UNIT;
  int x = col*UNIT;
  Black_King() {};
  void show();
};

extern Black_King BKing;

#endif // BLACK_KING_H
