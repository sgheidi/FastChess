#ifndef WHITE__H
#define WHITE__H

class White_Pieces : public Color {
private:
public:
  White_Pieces() {
    for (int i=0;i<8;i++) {
      blocks.push_back(std::vector<int>());
      for (int k=0;k<8;k++) {
        if (i == 6 || i == 7)
          blocks[i].push_back(1);
        else
          blocks[i].push_back(0);
      }
    }
    turn = true;
  };
  virtual ~White_Pieces() {};
  void check_kill(int row, int col);
  void move_piece(std::string piece, int row, int col);
  std::string get_piece(int row_, int col_);
  void play();
  void print_blocks();
  void show();
};

extern White_Pieces White;

#endif // WHITE__H
