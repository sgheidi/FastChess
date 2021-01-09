#ifndef MEDIA_TEXT_H
#define MEDIA_TEXT_H

#include <vector>

class Game_Text {
private:
  std::vector<int> color;
  sf::Font font;
  sf::Text text;
public:
  Game_Text() {
    color = {45, 16, 4};
    font.loadFromFile("assets/OpenSans.ttf");
  };
  void stalemate();
  void checkmate();
};

extern Game_Text Text;

#endif // MEDIA_TEXT_H
