#ifndef BLACK_ROOK_H
#define BLACK_ROOK_H

class Black_Rook : public Piece {
private:
public:
  Black_Rook() {
    alive = true;
    row = {0, 0};
    col = {0, 7};
    y = {row[0]*UNIT, row[1]*UNIT};
    x = {col[0]*UNIT, col[1]*UNIT};
  };
  void update_movelist();
  void show();
};

extern Black_Rook BRook;

#endif // BLACK_ROOK_H
