#ifndef BLACK_KNIGHT_H
#define BLACK_KNIGHT_H

class Black_Knight : public Piece {
private:
public:
  Black_Knight() {
    alive = true;
    row = {0, 0};
    col = {1, 6};
    y = {row[0]*UNIT, row[1]*UNIT};
    x = {col[0]*UNIT, col[1]*UNIT};
  };
  void update_movelist();
  void show();
};

extern Black_Knight BKnight;

#endif // BLACK_KNIGHT_H
