#include "common/config.h"
#include "common/util.h"

#include "board.h"
#include "queue.h"
#include "media/text.h"

#include "core/black/knight.h"
#include "core/black/pawn.h"
#include "core/black/rook.h"
#include "core/black/queen.h"
#include "core/black/king.h"

#include "core/white/bishop.h"
#include "core/white/knight.h"
#include "core/white/pawn.h"
#include "core/white/rook.h"
#include "core/white/queen.h"
#include "core/white/king.h"

#include "core/white_.h"
#include "core/black_.h"

#include "ai/black/search.h"

int main() {
  srand(time(NULL));
  Black::init();
  White::init();
  init(env);
  Board.update_moves();
  window.setPosition(sf::Vector2i(950, 180));
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
      || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        window.close();
      else if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
          case sf::Keyboard::B: Black::print_blocks(); break;
          case sf::Keyboard::W: White::print_blocks(); break;
          case sf::Keyboard::Z: Board.pop(); break;
          case sf::Keyboard::U: Board.print_undo(); break;
        }
      }
      else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i position = sf::Mouse::getPosition(window);
        if (position.x >= 1 && position.x <= X_RES-1 && position.y >= 1 && position.y <= Y_RES-1) {
          std::vector<int> pos = Board.get_coords(position.x, position.y);
          Board.selected_row = pos[1];
          Board.selected_col = pos[0];
          if (Board.clicked_piece == "K") {
            White::King.x = position.x - 3*Board.pieces_paddingx;
            White::King.y = position.y - 4*Board.pieces_paddingy;
          }
          for (int i=0;i<8;i++) {
            if (Board.clicked_piece == "P" + str(i)) {
              White::Pawn.x[i] = position.x - 3*Board.pieces_paddingx;
              White::Pawn.y[i] = position.y - 4*Board.pieces_paddingy;
            }
          }
          for (int i=0;i<White::num_queens;i++) {
            if (Board.clicked_piece == "Q" + str(i)) {
              White::Queen.x[i] = position.x - 3*Board.pieces_paddingx;
              White::Queen.y[i] = position.y - 4*Board.pieces_paddingy;
            }
          }
          for (int i=0;i<2;i++) {
            if (Board.clicked_piece == "B" + str(i)) {
              White::Bishop.x[i] = position.x - 3*Board.pieces_paddingx;
              White::Bishop.y[i] = position.y - 4*Board.pieces_paddingy;
            }
            else if (Board.clicked_piece == "N" + str(i)) {
              White::Knight.x[i] = position.x - 3*Board.pieces_paddingx;
              White::Knight.y[i] = position.y - 4*Board.pieces_paddingy;
            }
            else if (Board.clicked_piece == "R" + str(i)) {
              White::Rook.x[i] = position.x - 3*Board.pieces_paddingx;
              White::Rook.y[i] = position.y - 4*Board.pieces_paddingy;
            }
          }
        }
      }
      if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i position = sf::Mouse::getPosition(window);
        if (position.x >= 1 && position.x <= X_RES-1 && position.y >= 1 && position.y <= Y_RES-1) {
          std::vector<int> pos = Board.get_coords(position.x, position.y);
          Board.selected_row = pos[1];
          Board.selected_col = pos[0];
          Board.clicked_piece = White::get_piece(pos[1], pos[0]);
          Queue.enqueue(pos[1], pos[0]);
          Board.play();
        }
      }
      if (event.type == sf::Event::MouseButtonReleased) {
        Board.clicked_piece = "";
        Board.reset_pos();
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
    Board.show_legal_moves();
    Black::show();
    White::show();
    Board.check_end();
    window.display();
    White::check_capture_screen();
    Black::check_capture_screen();
    if (Black::is_AI && Black::turn && !Board.checkmate && !Board.stalemate)
      Black::AI::gen_move();
    window.display();
  }
  return 0;
}
