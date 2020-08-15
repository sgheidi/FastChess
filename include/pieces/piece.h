#ifndef PIECE_H
#define PIECE_H

class Piece {
protected:
public:
  std::vector<int> row, col, y, x;
  std::vector<std::vector<std::vector<int>>> movelist;
  std::vector<bool> alive;
};

#endif // PIECE_H
