#ifndef WHITE_KNIGHT_H
#define WHITE_KNIGHT_H

class White_Knight {
private:
public:
  std::vector<int> row = {7, 7};
  std::vector<int> col = {1, 6};
  std::vector<int> y = {row[0]*UNIT, row[1]*UNIT};
  std::vector<int> x = {col[0]*UNIT, col[1]*UNIT};
  White_Knight() {};
  void move(int i, int row_, int col_);
  void show();
};

extern White_Knight WKnight;

#endif // WHITE_KNIGHT_H
