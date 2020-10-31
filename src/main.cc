#include "common.h"

int main() {
  Black::init();
  White::init();
  init(env);
  Board.update_moves();
  window.setPosition(sf::Vector2i(950, 80));
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if ((event.type == sf::Event::Closed) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
      || (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)))
        window.close();
      else if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
          case sf::Keyboard::B: Black::print_blocks(); break;
          case sf::Keyboard::W: White::print_blocks(); break;
          case sf::Keyboard::Z: Board.pop(); break;
        }
      }
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
    if (Black::is_AI && Black::turn && !Board.checkmate && !Board.stalemate)
      Black::AI::gen_move();
    window.display();
  }
  return 0;
}
