#ifndef BOARD_H
#define BOARD_H

class Game_Board {
private:
  inline void drawRect(int*color, int x, int y, int width, int height);
public:
  struct undo;
  int row, col;
  int pieces_paddingx, pieces_paddingy;
  float pieces_scale;
  Game_Board() {
    row = -1;
    col = -1;
    pieces_paddingx = 9;
    pieces_paddingy = 5;
    pieces_scale = 1.63;
  };
  void update_moves();
  void arrow(int*start, int*end);
  void play();
  void draw_board();
  std::vector<int> get_coords(int x, int y);
  void select(int row, int col);
};

extern Game_Board Board;

#endif // BOARD_H
