#ifndef BLACK_PAWN_H
#define BLACK_PAWN_H

class Black_Pawn : public Piece {
private:
public:
  Black_Pawn() {
    alive = true;
    for (int i=0;i<8;i++) {
      row.push_back(1);
      col.push_back(i);
      y.push_back(row[i]*UNIT);
      x.push_back(col[i]*UNIT);
    }
  };
  void update_movelist();
  void show();
};

extern Black_Pawn BPawn;

#endif // BLACK_PAWN_H
