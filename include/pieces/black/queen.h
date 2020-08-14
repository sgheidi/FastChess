#ifndef BLACK_QUEEN_H
#define BLACK_QUEEN_H

namespace Black {

class Queen_Piece : public Piece {
private:
  int x, y;
public:
  int row, col;
  Queen_Piece() {
    alive = true;
    row = 0;
    col = 4;
    y = row*UNIT;
    x = col*UNIT;
  };
  void update_movelist();
  void show();
};

} // namespace Black

#endif // BLACK_QUEEN_H
