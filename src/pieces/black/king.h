#ifndef BLACK_KING_H
#define BLACK_KING_H

namespace Black {

class King_Piece : public Piece {
private:
public:
  std::vector<std::vector<int>> movelist, protecting_movelist;
  int x, y, row, col;
  bool alive;
  King_Piece() {
    alive = true;
    row = 0;
    col = 3;
    y = row*UNIT;
    x = col*UNIT;
  };
  void filter_king_pos();
  void filter_check_pos();
  void move(int row_, int col_);
  void update_movelist();
  void show();
};

} // namespace Black

#endif // BLACK_KING_H
