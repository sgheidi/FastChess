#include "../include/common.h"

int main() {
  Board.update_moves();
  window.setPosition(sf::Vector2i(250, 120));
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if ((event.type == sf::Event::Closed) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
      || (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)))
        window.close();
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
        Black.print_blocks();
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        White.print_blocks();
      else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (sf::Mouse::getPosition(window).x >= 0 && sf::Mouse::getPosition(window).x <= X_RES
        && sf::Mouse::getPosition(window).y >= 0 && sf::Mouse::getPosition(window).y <= Y_RES) {
          sf::Vector2i position = sf::Mouse::getPosition(window);
          std::vector<int> pos = Board.get_coords(position.x, position.y);
          Board.row = pos[1];
          Board.col = pos[0];
          Queue.enqueue(pos[1], pos[0]);
          Board.play();
        }
      }
    }
    window.clear();
    Board.draw_board();
    Board.select(Board.row, Board.col);
    White.show();
    Black.show();
    window.display();
  }
  return 0;
}
