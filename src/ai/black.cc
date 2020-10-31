#include "../common.h"

namespace Black { namespace AI {

void gen_move() {
  print("Generating move...");
  #ifdef DEBUGAI
  Log << "Generating move..." << std::endl;
  #endif
  std::map<std::string, std::string> best_move = {{"score", "-9999"}, {"piece", ""}, {"pos", ""}};
  std::map<std::string, std::vector<std::vector<int>>> moves = get_black_moves();
  std::map<std::string, std::vector<std::vector<int>>>::iterator itr;
  int score;
  Board.freeze = true;
  bool W_king_moved = White::King.moved;
  std::vector<bool> W_rook_moved = {White::Rook.moved[0], White::Rook.moved[1]};
  bool B_king_moved = Black::King.moved;
  std::vector<bool> B_rook_moved = {Black::Rook.moved[0], Black::Rook.moved[1]};
  for (itr=moves.begin();itr!=moves.end();itr++) {
    std::string piece = itr->first;
    std::vector<std::vector<int>> value = itr->second;
    for (int i=0;i<value.size();i++) {
      Black::move_piece(piece, value[i][0], value[i][1]);
      if (verbose) print("******************OUTER******************");
      if (verbose) std::cout << "****************** "<< piece << " " << value[i][0] << " " << value[i][1]
      << "******************" << std::endl;
      #ifdef DEBUGAI
      Log << "******************OUTER******************" << std::endl;
      Log << "****************** "<< piece << " " << value[i][0] << " " << value[i][1]
      << "******************" << std::endl;
      #endif
      score = minimax(Black::depth, -10000, 10000, "W");
      Board.pop();
      if (score >= std::stoi(best_move["score"])) {
        best_move["score"] = str(score);
        best_move["piece"] = piece;
        best_move["pos"] = str(value[i][0]) + str(value[i][1]);
      }
    }
  }
  Board.freeze = false;
  if (best_move["piece"] == "") {
    #ifdef DEBUGAI
    Log << "No moves left!" << std::endl;
    #endif
    print("No moves left!");
    exit(1);
  }
  Black::move_piece(best_move["piece"], best_move["pos"][0]-'0', best_move["pos"][1]-'0');
  if (!testing) {
    Black::turn = false;
    White::turn = true;
  }
  White::Rook.moved[0] = W_rook_moved[0];
  White::Rook.moved[1] = W_rook_moved[1];
  Black::Rook.moved[0] = B_rook_moved[0];
  Black::Rook.moved[1] = B_rook_moved[1];
  White::King.moved = W_king_moved;
  Black::King.moved = B_king_moved;
}

int minimax(int n, int alpha, int beta, std::string player) {
  std::map<std::string, std::vector<std::vector<int>>> black_moves = get_black_moves();
  std::map<std::string, std::vector<std::vector<int>>> white_moves = get_white_moves();
  std::map<std::string, std::vector<std::vector<int>>>::iterator itr;
  int best_move;
  if (n == 0)
    return -evaluate_pos();
  // minimizing player
  if (player == "B") {
    best_move = -9999;
    for (itr=black_moves.begin();itr!=black_moves.end();itr++) {
      std::string piece = itr->first;
      std::vector<std::vector<int>> value = itr->second;
      for (int i=0;i<value.size();i++) {
        Black::move_piece(piece, value[i][0], value[i][1]);
        if (verbose) print("INNER BLACK");
        if (verbose) std::cout << piece << " " << value[i][0] << " " << value[i][1] << std::endl;
        #ifdef DEBUGAI
        Log << "INNER BLACK" << std::endl;
        Log << piece << " " << value[i][0] << " " << value[i][1] << std::endl;
        #endif
        best_move = std::max(best_move, minimax(n-1, alpha, beta, "W"));
        Board.pop();
        alpha = std::max(alpha, best_move);
        if (beta <= alpha)
          return best_move;
      }
    }
  }
  // maximizing player
  else {
    best_move = 9999;
    for (itr=white_moves.begin();itr!=white_moves.end();itr++) {
      std::string piece = itr->first;
      std::vector<std::vector<int>> value = itr->second;
      for (int i=0;i<value.size();i++) {
        White::move_piece(piece, value[i][0], value[i][1]);
        if (verbose) print("INNER WHITE");
        if (verbose) std::cout << piece << " " << value[i][0] << " " << value[i][1] << std::endl;
        #ifdef DEBUGAI
        Log << "INNER WHITE" << std::endl;
        Log << piece << " " << value[i][0] << " " << value[i][1] << std::endl;
        #endif
        best_move = std::min(best_move, minimax(n-1, alpha, beta, "B"));
        Board.pop();
        beta = std::min(beta, best_move);
        if (beta <= alpha)
          return best_move;
      }
    }
  }
  return best_move;
}

} // namespace AI
} // namespace Black
