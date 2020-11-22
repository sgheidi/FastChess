#include "../../common.h"

namespace Black::AI {

void gen_move() {
  print("Generating move...");
  #ifdef DEBUGAI
  Log << "Generating move..." << std::endl;
  #endif
  std::map<std::string, std::string> best_move = {{"score", "-9999"}, {"piece", ""}, {"pos", ""}};
  std::map<std::string, std::vector<std::vector<int>>> moves = get_black_moves();
  std::map<std::string, std::vector<std::vector<int>>> temp = moves;
  std::map<std::string, std::vector<std::vector<int>>>::iterator itr;
  double score;
  Board.freeze = true;
  bool W_king_moved = White::King.moved;
  std::vector<bool> W_rook_moved = {White::Rook.moved[0], White::Rook.moved[1]};
  bool B_king_moved = Black::King.moved;
  std::vector<bool> B_rook_moved = {Black::Rook.moved[0], Black::Rook.moved[1]};
  for (itr=temp.begin();itr!=temp.end();itr++) {
    std::string piece = random_key(moves);
    std::vector<std::vector<int>> value = moves[piece];
    for (int i=0;i<value.size();i++) {
      if (piece == "CK")
        Black::castle_K(false);
      if (piece == "CQ")
        Black::castle_Q(false);
      else
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
      if (verbose2) std::cout << piece << " (" << value[i][0] << " " << value[i][1] << ") "
      << score << std::endl;
      Board.pop();
      if (score >= std::stoi(best_move["score"])) {
        best_move["score"] = str(score);
        best_move["piece"] = piece;
        best_move["pos"] = str(value[i][0]) + str(value[i][1]);
      }
    }
    moves.erase(piece);
  }
  Board.freeze = false;
  if (best_move["piece"] == "") {
    #ifdef DEBUGAI
    Log << "No moves left!" << std::endl;
    #endif
    print("No moves left!");
    exit(1);
  }
  if (best_move["piece"] == "CK")
    Black::castle_K(false);
  else if (best_move["piece"] == "CQ")
    Black::castle_Q(false);
  else
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

double minimax(int n, double alpha, double beta, std::string player) {
  std::map<std::string, std::vector<std::vector<int>>> black_moves = get_black_moves();
  std::map<std::string, std::vector<std::vector<int>>> white_moves = get_white_moves();
  std::map<std::string, std::vector<std::vector<int>>> btemp = black_moves;
  std::map<std::string, std::vector<std::vector<int>>> wtemp = white_moves;
  std::map<std::string, std::vector<std::vector<int>>>::iterator itr;
  double best_move;
  if (n == 0)
    return -evaluate_pos();
  // minimizing player
  if (player == "B") {
    best_move = -9999;
    for (itr=btemp.begin();itr!=btemp.end();itr++) {
      std::string piece = random_key(black_moves);
      std::vector<std::vector<int>> value = black_moves[piece];
      for (int i=0;i<value.size();i++) {
        if (piece == "CK" || piece == "CQ") continue;
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
      black_moves.erase(piece);
    }
  }
  // maximizing player
  else {
    best_move = 9999;
    for (itr=wtemp.begin();itr!=wtemp.end();itr++) {
      std::string piece = random_key(white_moves);
      std::vector<std::vector<int>> value = white_moves[piece];
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
      white_moves.erase(piece);
    }
  }
  return best_move;
}

} // namespace Black::AI
