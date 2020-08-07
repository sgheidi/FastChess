#ifndef BLACK__H
#define BLACK__H

class Black_Pieces {
private:
public:
  bool turn;
  std::vector<std::vector<int>> blocks;
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
    turn = false;
  };
  void play();
  void print_blocks();
  void show();
};

extern Black_Pieces Black;

#endif // BLACK__H
