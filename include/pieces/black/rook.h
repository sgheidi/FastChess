#ifndef BLACK_ROOK_H
#define BLACK_ROOK_H

class Black_Rook {
private:
public:
  bool alive = true;
  std::vector<int> row = {0, 0};
  std::vector<int> col = {0, 7};
  std::vector<int> y = {row[0]*UNIT, row[1]*UNIT};
  std::vector<int> x = {col[0]*UNIT, col[1]*UNIT};
  Black_Rook() {};
  void update_movelist();
  void show();
};

extern Black_Rook BRook;

#endif // BLACK_ROOK_H
