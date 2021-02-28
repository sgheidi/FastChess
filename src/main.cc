#include "common/config.h"
#include "common/util.h"
#include "board.h"
#include "queue.h"
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

#define WINDOW_X_POS 950
#define WINDOW_Y_POS 180

int main() {
  srand(time(NULL));
  black::init();
  white::init();
  init(GAME_ENV);
  board.update_moves();
  window.setPosition(sf::Vector2i(WINDOW_X_POS, WINDOW_Y_POS));
  while (window.isOpen()) {
    static sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) 
      || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        window.close();
      else if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
          case sf::Keyboard::B: black::print_blocks(); break;
          case sf::Keyboard::W: white::print_blocks(); break;
          case sf::Keyboard::Z: board.pop(); break;
          case sf::Keyboard::U: board.print_undo(); break;
        }
      }
      // Drag and drop (left mouse button is held)
      else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (board.selected_row != -1 && board.selected_col != -1 && board.clicked_coords[0] != -1
        && board.clicked_coords[1] != -1) {
          if (white::turn && white::blocks[board.clicked_coords[0]][board.clicked_coords[1]])
            white::drag_and_drop();
        }
        #ifndef IS_BLACK_AI
        if (board.selected_row != -1 && board.selected_col != -1 && board.clicked_coords[0] != -1
        && board.clicked_coords[1] != -1) {
          if (black::turn && black::blocks[board.clicked_coords[0]][board.clicked_coords[1]])
            black::drag_and_drop();
        }
        #endif
      }
      // Click a piece to enqueue it to the game (clicking) queue
      if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i position = sf::Mouse::getPosition(window);
        if (position.x >= 1 && position.x <= X_RES-1 && position.y >= 1 && position.y <= Y_RES-1) {
          std::vector<int> pos = board.get_coords(position.x, position.y);
          board.selected_row = pos[1];
          board.selected_col = pos[0];
          if (white::blocks[board.selected_row][board.selected_col]) {
            board.clicked_piece = white::get_piece(pos[1], pos[0]);
            board.clicked_coords = {pos[1], pos[0]};
            white::last_clicked_piece = white::get_piece(pos[1], pos[0]);
            if (board.clicked_piece != "") {
              queue.enqueue(pos[1], pos[0]);
              board.play();
            }
          }
          #ifndef IS_BLACK_AI
          else if (black::blocks[board.selected_row][board.selected_col]) {
            board.clicked_piece = black::get_piece(pos[1], pos[0]);
            board.clicked_coords = {pos[1], pos[0]};
            black::last_clicked_piece = black::get_piece(pos[1], pos[0]);
            if (board.clicked_piece != "") {
              queue.enqueue(pos[1], pos[0]);
              board.play();
            }
          }
          #endif
        }
      }
      if (event.type == sf::Event::MouseButtonReleased) {
        board.clicked_piece = "";
        white::reset_sprite_pos();
        black::reset_sprite_pos();
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
    black::show();
    white::show();
    if (white::turn && board.clicked_coords[0] != -1 && board.clicked_coords[1] != -1)
      if (white::blocks[board.clicked_coords[0]][board.clicked_coords[1]])
        white::show_legal_moves();
    #if !defined(IS_BLACK_AI)
    if (black::turn && board.clicked_coords[0] != -1 && board.clicked_coords[1] != -1)
      if (black::blocks[board.clicked_coords[0]][board.clicked_coords[1]])
        black::show_legal_moves();
    #endif
    board.check_end();
    window.display();
    #ifdef SCREENSHOTS_ON
    white::check_capture_screen();
    black::check_capture_screen();
    #endif
    #ifdef IS_BLACK_AI
    if (black::turn && !board.checkmate && !board.stalemate)
      black::ai::gen_move();
    #endif
    window.display();
  }
  return 0;
}
