#include "common.h"

int main() {
  Black::init();
  White::init();
  Board.update_moves();
  window.setPosition(sf::Vector2i(250, 120));
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if ((event.type == sf::Event::Closed) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
      || (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)))
        window.close();
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
        Black::print_blocks();
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        White::print_blocks();
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        Board.pop();
      else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i position = sf::Mouse::getPosition(window);
        if (position.x >= 1 && position.x <= X_RES-1 && position.y >= 1 && position.y <= Y_RES-1) {
          std::vector<int> pos = Board.get_coords(position.x, position.y);
          Board.selected_row = pos[1];
          Board.selected_col = pos[0];
          Queue.enqueue(pos[1], pos[0]);
          Board.play();
        }
      }
    }
    window.clear();
    Board.draw_board();
    Board.select(Board.selected_row, Board.selected_col);
    White::show();
    Black::show();
    Board.check_end();
    window.display();
  }
  return 0;
}
