#ifndef PIECE_H
#define PIECE_H

class Piece {
protected:
  sf::Sprite sprite;
  sf::Texture texture;
public:
  std::vector<int> row, col, y, x;
  std::vector<std::vector<std::vector<int>>> movelist, protecting_movelist, hit_movelist;
  std::vector<bool> alive;
};

#endif // PIECE_H
