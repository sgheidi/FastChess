#ifndef PIECE_H
#define PIECE_H

class Piece {
protected:
  std::vector<int> y;
  std::vector<int> x;
public:
  std::vector<int> row;
  std::vector<int> col;
  std::vector<std::vector<std::vector<int>>> movelist;
  bool alive;
};

#endif // PIECE_H
