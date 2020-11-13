#ifndef BOARD_H
#define BOARD_H

class Game_Board {
private:
  inline void drawRect(int*color, int x, int y, int width, int height);
public:
  int total_moves;
  int selected_row, selected_col;
  int pieces_paddingx, pieces_paddingy;
  float pieces_scale;
  bool checkmate, stalemate;
  bool freeze;
  int screenshot_num;
  Game_Board() {
    screenshot_num = 1;
    selected_row = selected_col = -1;
    checkmate = false;
    stalemate = false;
    total_moves = 0;
    pieces_paddingx = 9;
    pieces_paddingy = 5;
    pieces_scale = 1.63;
    freeze = false;
  };
  void print_undo();
  void save_enpassant();
  void load_enpassant();
  void check_end();
  void pop();
  void update_moves();
  void play();
  void draw_board();
  std::vector<int> get_coords(int x, int y);
  void select(int row, int col);
};

extern Game_Board Board;

#endif // BOARD_H
