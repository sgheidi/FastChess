#ifndef WHITE_QUEEN_H
#define WHITE_QUEEN_H

namespace White {

class Queen_Piece : public Piece {
private:
  void pin(int i, std::string);
  std::string get_pinned_piece(int i);
  int num_pieces(int i);
  bool king_in_path(int i);
public:
  Queen_Piece() {
    row = {7};
    col = {3};
    y = {row[0]*UNIT};
    x = {col[0]*UNIT};
    alive = {true};
    movelist.resize(1);
    protecting_movelist.resize(1);
  };
  void pure_move(int i, int row_, int col_);
  void check_pin();
  std::vector<int> get_avoid_move(int i);
  std::vector<std::vector<int>> get_check_movelist(int i);
  void update_movelist();
  void move(int i, int row_, int col_);
  void show();
};

extern Queen_Piece Queen;

} // namespace White

#endif // WHITE_QUEEN_H
