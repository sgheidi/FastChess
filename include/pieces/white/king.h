#ifndef WHITE_KING_H
#define WHITE_KING_H

namespace White {

class King_Piece : public Piece {
private:
public:
  std::vector<std::vector<int>> movelist, protecting_movelist;
  int row, col, y, x;
  bool alive;
  King_Piece() {
    row = 7;
    col = 3;
    y = row*UNIT;
    x = col*UNIT;
    alive = true;
  };
  void filter_king_pos();
  void filter_check_pos();
  void update_movelist();
  void move(int row_, int col_);
  void show();
};

} // namespace White

#endif // WHITE_KING_H
