#ifndef WHITE_PAWN_H
#define WHITE_PAWN_H

class White_Pawn {
private:
  std::vector<int> y;
  std::vector<int> x;
public:
  bool alive = true;
  std::vector<int> row;
  std::vector<int> col;
  std::vector<std::vector<std::vector<int>>> movelist;
  White_Pawn() {
    for (int i=0;i<8;i++) {
      row.push_back(6);
      col.push_back(i);
      y.push_back(row[i]*UNIT);
      x.push_back(col[i]*UNIT);
    }
    movelist.resize(8);
  };
  void update_movelist();
  void move(int i, int row_, int col_);
  void show();
};

extern White_Pawn WPawn;

#endif // WHITE_PAWN_H
