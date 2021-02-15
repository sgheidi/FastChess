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

#ifdef IS_BLACK_AI
#include "ai/black/search.h"
#endif

int main() {
  srand(time(NULL));
  Black::init();
  White::init();
  init(GAME_ENV);
  board.update_moves();
  window.setPosition(sf::Vector2i(950, 180));
  while (window.isOpen()) {
    static sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        window.close();
      else if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
          case sf::Keyboard::B: Black::print_blocks(); break;
          case sf::Keyboard::W: White::print_blocks(); break;
          case sf::Keyboard::Z: board.pop(); break;
          case sf::Keyboard::U: board.print_undo(); break;
        }
      }
      else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i position = sf::Mouse::getPosition(window);
        if (position.x >= 1 && position.x <= X_RES-1 && position.y >= 1 && position.y <= Y_RES-1) {
          std::vector<int> pos = board.get_coords(position.x, position.y);
          board.selected_row = pos[1];
          board.selected_col = pos[0];
          if (board.clicked_piece == "K") {
            White::king.x = position.x - 3*board.pieces_paddingx;
            White::king.y = position.y - 4*board.pieces_paddingy;
          }
          for (int i=0;i<8;i++) {
            if (board.clicked_piece == "P" + str(i)) {
              White::pawn.x[i] = position.x - 3*board.pieces_paddingx;
              White::pawn.y[i] = position.y - 4*board.pieces_paddingy;
            }
          }
          for (int i=0;i<White::num_queens;i++) {
            if (board.clicked_piece == "Q" + str(i)) {
              White::queen.x[i] = position.x - 3*board.pieces_paddingx;
              White::queen.y[i] = position.y - 4*board.pieces_paddingy;
            }
          }
          for (int i=0;i<2;i++) {
            if (board.clicked_piece == "B" + str(i)) {
              White::bishop.x[i] = position.x - 3*board.pieces_paddingx;
              White::bishop.y[i] = position.y - 4*board.pieces_paddingy;
            }
            else if (board.clicked_piece == "N" + str(i)) {
              White::knight.x[i] = position.x - 3*board.pieces_paddingx;
              White::knight.y[i] = position.y - 4*board.pieces_paddingy;
            }
            else if (board.clicked_piece == "R" + str(i)) {
              White::rook.x[i] = position.x - 3*board.pieces_paddingx;
              White::rook.y[i] = position.y - 4*board.pieces_paddingy;
            }
          }
        }
      }
      if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i position = sf::Mouse::getPosition(window);
        if (position.x >= 1 && position.x <= X_RES-1 && position.y >= 1 && position.y <= Y_RES-1) {
          std::vector<int> pos = board.get_coords(position.x, position.y);
          board.selected_row = pos[1];
          board.selected_col = pos[0];
          board.clicked_piece = White::get_piece(pos[1], pos[0]);
          queue.enqueue(pos[1], pos[0]);
          board.play();
        }
      }
      if (event.type == sf::Event::MouseButtonReleased) {
        board.clicked_piece = "";
        board.reset_pos();
        sf::Vector2i position = sf::Mouse::getPosition(window);
        if (position.x >= 1 && position.x <= X_RES-1 && position.y >= 1 && position.y <= Y_RES-1) {
          std::vector<int> pos = board.get_coords(position.x, position.y);
          board.selected_row = pos[1];
          board.selected_col = pos[0];
          queue.enqueue(pos[1], pos[0]);
          board.play();
        }
      }
    }
    window.clear();
    board.draw_board();
    board.select(board.selected_row, board.selected_col);
    board.show_legal_moves();
    Black::show();
    White::show();
    board.check_end();
    window.display();
    #ifdef SCREENSHOTS_ON
    White::check_capture_screen();
    Black::check_capture_screen();
    #endif
    #ifdef IS_BLACK_AI
    if (Black::turn && !board.checkmate && !board.stalemate)
      Black::AI::gen_move();
    #endif
    window.display();
  }
  return 0;
}
