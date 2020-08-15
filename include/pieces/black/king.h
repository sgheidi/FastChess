#ifndef BLACK_KING_H
#define BLACK_KING_H

namespace Black {

class King_Piece : public Piece {
private:
public:
  int x, y, row, col;
  bool alive;
  King_Piece() {
    alive = true;
    row = 0;
    col = 3;
    y = row*UNIT;
    x = col*UNIT;
  };
  void update_movelist();
  void show();
};

} // namespace Black

#endif // BLACK_KING_H
