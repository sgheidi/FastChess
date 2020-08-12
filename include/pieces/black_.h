#ifndef BLACK__H
#define BLACK__H

class Black_Pieces : public Color {
private:
public:
  Black_Pieces() {
    for (int i=0;i<8;i++) {
      blocks.push_back(std::vector<int>());
      for (int k=0;k<8;k++) {
        if (i == 0 || i == 1)
          blocks[i].push_back(1);
        else
          blocks[i].push_back(0);
      }
    }
    turn = true;
  };
  void move_piece(std::string piece, int row, int col);
  std::string get_piece(int row_, int col_);
  void play();
  void print_blocks();
  void show();
};

extern Black_Pieces Black;

#endif // BLACK__H
