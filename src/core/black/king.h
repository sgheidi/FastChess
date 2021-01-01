#ifndef BLACK_KING_H
#define BLACK_KING_H

namespace Black {

class King_Piece : public Piece {
private:
public:
  bool moved;
  std::vector<std::vector<int>> movelist, protecting_movelist;
  int x, y, row, col;
  bool alive;
  King_Piece() {
    moved = 0;
    alive = true;
    row = 0;
    col = 4;
    y = row*UNIT;
    x = col*UNIT;
  };
  void filter_king_pos();
  void filter_check_pos();
  void move(int row_, int col_);
  void update_movelist();
  void show();
};

extern King_Piece King;

} // namespace Black

#endif // BLACK_KING_H
