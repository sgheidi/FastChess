#ifndef WHITE_PAWN_H
#define WHITE_PAWN_H

class White_Pawn : public Piece {
private:
public:
  std::vector<std::vector<std::vector<int>>> movelist;
  White_Pawn() {
    for (int i=0;i<8;i++) {
      row.push_back(6);
      col.push_back(i);
      y.push_back(row[i]*UNIT);
      x.push_back(col[i]*UNIT);
    }
    alive = true;
    movelist.resize(8);
  };
  void print_movelist();
  void update_movelist();
  void move(int i, int row_, int col_);
  void show();
};

extern White_Pawn WPawn;

#endif // WHITE_PAWN_H
