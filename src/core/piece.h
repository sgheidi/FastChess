#ifndef CORE_PIECE_H
#define CORE_PIECE_H

// The abstract base class from which all other piece classes (King, Queen, Bishop,...etc) inherit attributes from
class Piece {
protected:
public:
  sf::Sprite sprite;
  sf::Texture texture;
  std::vector<int> row, col, y, x;
  std::vector<std::vector<std::vector<int>>> movelist, protecting_movelist, hit_movelist;
  std::vector<bool> alive;
};

#endif // CORE_PIECE_H
