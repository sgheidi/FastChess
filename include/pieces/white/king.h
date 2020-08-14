#ifndef WHITE_KING_H
#define WHITE_KING_H

namespace White {

class King_Piece : public Piece {
private:
  int x, y;
public:
  std::vector<std::vector<int>> movelist;
  int row, col;
  King_Piece() {
    row = 7;
    col = 3;
    y = row*UNIT;
    x = col*UNIT;
    movelist = {};
    alive = true;
  };
  void update_movelist();
  void move(int row_, int col_);
  void show();
};

} // namespace White

#endif // WHITE_KING_H
