#ifndef WHITE_KING_H
#define WHITE_KING_H

namespace White {

class King_Piece : public Piece {
private:
public:
  bool moved;
  std::vector<std::vector<int>> movelist, protecting_movelist;
  int row, col, y, x;
  bool alive;
  King_Piece() {
    moved = 0;
    alive = true;
    row = 7;
    col = 4;
    y = row*UNIT;
    x = col*UNIT;
  };
  void filter_king_pos();
  void filter_check_pos();
  void update_movelist();
  void move(int row_, int col_);
  void show();
};

extern King_Piece King;

} // namespace White

#endif // WHITE_KING_H
