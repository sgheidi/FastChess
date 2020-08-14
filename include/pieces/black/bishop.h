#ifndef BLACK_BISHOP_H
#define BLACK_BISHOP_H

namespace Black {

class Bishop_Piece : public Piece {
private:
public:
  Bishop_Piece() {
    alive = true;
    row = {0, 0};
    col = {2, 5};
    y = {row[0]*UNIT, row[1]*UNIT};
    x = {col[0]*UNIT, col[1]*UNIT};
  };
  void update_movelist();
  void show();
};

} // namespace Black

#endif // BLACK_BISHOP_H
