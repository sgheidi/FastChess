#ifndef BLACK_PAWN_H
#define BLACK_PAWN_H

namespace Black {

class Pawn_Piece : public Piece {
private:
public:
  std::vector<std::vector<std::vector<int>>> movelist;
  Pawn_Piece() {
    for (int i=0;i<8;i++) {
      row.push_back(1);
      col.push_back(i);
      y.push_back(row[i]*UNIT);
      x.push_back(col[i]*UNIT);
      alive.push_back(1);
    }
    movelist.resize(8);
  };
  void move(int i, int row_, int col_);
  void update_movelist();
  void show();
};

} // namespace Black

#endif // BLACK_PAWN_H
