#ifndef BLACK_ROOK_H
#define BLACK_ROOK_H

namespace Black {

class Rook_Piece : public Piece {
private:
public:
  Rook_Piece() {
    alive = {1, 1};
    movelist.resize(2);
    row = {0, 0};
    col = {0, 7};
    y = {row[0]*UNIT, row[1]*UNIT};
    x = {col[0]*UNIT, col[1]*UNIT};
    protecting_movelist.resize(2);
  };
  void pin(int i, std::string);
  std::string get_pinned_piece(int i);
  int num_pieces(int i);
  void check_pin();
  bool king_in_path(int i);
  std::vector<int> get_avoid_move(int i);
  std::vector<std::vector<int>> get_check_movelist(int i);
  void move(int i, int row_, int col_);
  void update_movelist();
  void show();
};

} // namespace Black

#endif // BLACK_ROOK_H
