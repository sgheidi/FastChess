#ifndef WHITE_ROOK_H
#define WHITE_ROOK_H

class White_Rook {
private:
public:
  bool alive = true;
  std::vector<int> row = {7, 7};
  std::vector<int> col = {0, 7};
  std::vector<int> y = {row[0]*UNIT, row[1]*UNIT};
  std::vector<int> x = {col[0]*UNIT, col[1]*UNIT};
  White_Rook() {};
  void update_movelist();
  void move(int i, int row_, int col_);
  void show();
};

extern White_Rook WRook;

#endif // WHITE_ROOK_H
