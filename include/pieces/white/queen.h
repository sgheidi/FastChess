#ifndef WHITE_QUEEN_H
#define WHITE_QUEEN_H

namespace White {

class Queen_Piece : public Piece {
private:
public:
  std::vector<std::vector<int>> movelist;
  int row, col, y, x;
  bool alive;
  Queen_Piece() {
    row = 7;
    col = 4;
    y = row*UNIT;
    x = col*UNIT;
    alive = true;
  };
  void update_movelist();
  void move(int row_, int col_);
  void show();
};

} // namespace White

#endif // WHITE_QUEEN_H
