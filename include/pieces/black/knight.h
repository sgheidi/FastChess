#ifndef BLACK_KNIGHT_H
#define BLACK_KNIGHT_H

namespace Black {

class Knight_Piece : public Piece {
private:
public:
  Knight_Piece() {
    alive = true;
    row = {0, 0};
    col = {1, 6};
    y = {row[0]*UNIT, row[1]*UNIT};
    x = {col[0]*UNIT, col[1]*UNIT};
  };
  void update_movelist();
  void show();
};

} // namespace Black

#endif // BLACK_KNIGHT_H
