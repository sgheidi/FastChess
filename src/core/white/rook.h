#ifndef CORE_WHITE_ROOK_H
#define CORE_WHITE_ROOK_H

#include "../piece.h"

namespace White {

class Rook_Piece : public Piece {
private:
  void pin(int i, std::string);
  std::string get_pinned_piece(int i);
  int num_pieces(int i);
  bool king_in_path(int i);
public:
  std::vector<bool> moved;
  Rook_Piece() {
    moved = {0, 0};
    alive = {1, 1};
    movelist.resize(2);
    protecting_movelist.resize(2);
    row = {7, 7};
    col = {0, 7};
    y = {row[0]*UNIT, row[1]*UNIT};
    x = {col[0]*UNIT, col[1]*UNIT};
  };
  void pure_move(int i, int row_, int col_);
  void check_pin();
  std::vector<int> get_avoid_move(int i);
  std::vector<std::vector<int>> get_check_movelist(int i);
  void move(int i, int row_, int col_);
  void update_movelist();
  void show();
};

extern Rook_Piece rook;

} // namespace White

#endif // CORE_WHITE_ROOK_H
