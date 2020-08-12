#ifndef COLOR_H
#define COLOR_H

class Color {
protected:
public:
  bool turn;
  std::vector<std::vector<int>> blocks;
  void check_kill(int row, int col);
  void move_piece(std::string piece, int row, int col);
  std::string get_piece(int row_, int col_);
  void play();
  void print_blocks();
  void show();
};

#endif // COLOR_H
