#ifndef WHITE_BISHOP_H
#define WHITE_BISHOP_H

class White_Bishop {
private:
public:
  std::vector<int> row = {7, 7};
  std::vector<int> col = {2, 5};
  std::vector<int> y = {row[0]*UNIT, row[1]*UNIT};
  std::vector<int> x = {col[0]*UNIT, col[1]*UNIT};
  White_Bishop() {};
  void move(int i, int row_, int col_);
  void show();
};

extern White_Bishop WBishop;

#endif // WHITE_BISHOP_H
