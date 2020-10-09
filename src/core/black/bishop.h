#ifndef BLACK_BISHOP_H
#define BLACK_BISHOP_H

namespace Black {

class Bishop_Piece : public Piece {
private:
  void pin(int i, std::string);
  std::string get_pinned_piece(int i);
  int num_pieces(int i);
  bool king_in_path(int i);
public:
  Bishop_Piece() {
    alive = {1, 1};
    movelist.resize(2);
    protecting_movelist.resize(2);
    row = {0, 0};
    col = {2, 5};
    y = {row[0]*UNIT, row[1]*UNIT};
    x = {col[0]*UNIT, col[1]*UNIT};
  };
  void check_pin();
  std::vector<int> get_avoid_move(int i);
  std::vector<std::vector<int>> get_check_movelist(int i);
  void move(int i, int row_, int col_);
  void pure_move(int i, int row_, int col_);
  void update_movelist();
  void show();
};

} // namespace Black

#endif // BLACK_BISHOP_H
