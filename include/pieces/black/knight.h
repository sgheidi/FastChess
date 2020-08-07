#ifndef BLACK_KNIGHT_H
#define BLACK_KNIGHT_H

class Black_Knight {
private:
public:
  std::vector<int> row = {0, 0};
  std::vector<int> col = {1, 6};
  std::vector<int> y = {row[0]*UNIT, row[1]*UNIT};
  std::vector<int> x = {col[0]*UNIT, col[1]*UNIT};
  Black_Knight() {};
  void show();
};

extern Black_Knight BKnight;

#endif // BLACK_KNIGHT_H
