#ifndef BLACK_QUEEN_H
#define BLACK_QUEEN_H

namespace Black {

class Queen_Piece : public Piece {
private:
public:
  Queen_Piece() {
    row = {0};
    col = {4};
    y = {row[0]*UNIT};
    x = {col[0]*UNIT};
    alive = {true};
    movelist.resize(1);
    protecting_movelist.resize(1);
  };
  void update_movelist();
  void move(int i, int row_, int col_);
  void show();
};

} // namespace Black

#endif // BLACK_QUEEN_H
