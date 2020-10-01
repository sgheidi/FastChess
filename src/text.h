#ifndef TEXT_H
#define TEXT_H

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

#endif // TEXT_H
