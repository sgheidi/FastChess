#ifndef WHITE_KING_H
#define WHITE_KING_H

class White_King {
private:
public:
  bool alive = true;
  int row = 7;
  int col = 3;
  int y = row*UNIT;
  int x = col*UNIT;
  std::vector<std::vector<int>> movelist = {};
  White_King() {};
  void update_movelist();
  void move(int row_, int col_);
  void show();
};

extern White_King WKing;

#endif // WHITE_KING_H
