#ifndef BOARD_H
#define BOARD_H

class Game_Board {
public:
  int total_moves;
  int selected_row, selected_col;
  int pieces_paddingx, pieces_paddingy;
  float pieces_scale;
  bool checkmate, stalemate;
  bool isFrozen;
  int screenshot_num;
  std::string clicked_piece;
  Game_Board() {
    clicked_piece = "";
    screenshot_num = 1;
    selected_row = selected_col = -1;
    checkmate = false;
    stalemate = false;
    total_moves = 0;
    pieces_paddingx = 13;
    pieces_paddingy = 8;
    pieces_scale = 1;
    isFrozen = false;
  };
  void Circle(int row, int col);
  void reset_pos();
  void print_undo();
  void check_end();
  void pop();
  void update_moves();
  void play();
  void draw_board();
  std::vector<int> get_coords(int x, int y);
  void select(int row, int col);
private:
  void drawRect(int* color, int x, int y, int width, int height);
  };

extern Game_Board board;

#endif // BOARD_H
