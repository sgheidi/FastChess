#ifndef WHITE_PAWN_H
#define WHITE_PAWN_H

namespace White {

class Pawn_Piece : public Piece {
private:
public:
  Pawn_Piece() {
    for (int i=0;i<8;i++) {
      row.push_back(6);
      col.push_back(i);
      y.push_back(row[i]*UNIT);
      x.push_back(col[i]*UNIT);
      alive.push_back(1);
    }
    movelist.resize(8);
    hit_movelist.resize(8);
  };
  void pure_move(int i, int row_, int col_);
  void move(int i, int row_, int col_);
  void print_movelist();
  void update_movelist();
  void show();
};

extern Pawn_Piece Pawn;

} // namespace White

#endif // WHITE_PAWN_H
