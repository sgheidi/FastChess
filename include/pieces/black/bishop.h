#ifndef BLACK_BISHOP_H
#define BLACK_BISHOP_H

class Black_Bishop {
private:
public:
  bool alive = true;
  std::vector<int> row = {0, 0};
  std::vector<int> col = {2, 5};
  std::vector<int> y = {row[0]*UNIT, row[1]*UNIT};
  std::vector<int> x = {col[0]*UNIT, col[1]*UNIT};
  Black_Bishop() {};
  void update_movelist();
  void show();
};

extern Black_Bishop BBishop;

#endif // BLACK_BISHOP_H
