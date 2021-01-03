#include "../../common/config.h"
#include "../../common/util.h"

#include "../../board.h"

#include "../../core/black/bishop.h"
#include "../../core/black/knight.h"
#include "../../core/black/pawn.h"
#include "../../core/black/rook.h"
#include "../../core/black/queen.h"
#include "../../core/black/king.h"

#include "../../core/white/bishop.h"
#include "../../core/white/knight.h"
#include "../../core/white/pawn.h"
#include "../../core/white/rook.h"
#include "../../core/white/queen.h"
#include "../../core/white/king.h"

#include "../../core/white_.h"
#include "../../core/black_.h"

#include "../helper.h"
#include "../white/eval.h"
#include "eval.h"
#include "search.h"

namespace Black::AI {
void gen_move() {
  print("Generating move...");
  #ifdef DEBUGAI
  Log << "Generating move..." << std::endl;
  #endif
  std::map<std::string, std::string> best_move = {{"score", "-9999"}, {"piece", ""}, {"pos", ""}};
  std::map<std::string, std::vector<std::vector<int>>> moves = Black::get_moves();
  std::map<std::string, std::vector<std::vector<int>>> temp = moves;
  double score;
  Board.freeze = true;
  bool W_king_moved = White::King.moved;
  std::vector<bool> W_rook_moved = {White::Rook.moved[0], White::Rook.moved[1]};
  bool B_king_moved = Black::King.moved;
  std::vector<bool> B_rook_moved = {Black::Rook.moved[0], Black::Rook.moved[1]};
  std::vector<double> scores = {};
  for (std::map<std::string, std::vector<std::vector<int>>>::iterator itr=temp.begin();itr!=temp.end();itr++) {
    std::string piece = random_key(moves);
    std::vector<std::vector<int>> value = moves[piece];
    for (int i=0;i<value.size();i++) {
      if (piece == "CK")
        Black::castle_K(false);
      if (piece == "CQ")
        Black::castle_Q(false);
      else
        Black::move_piece(piece, value[i][0], value[i][1]);
      if (verbose2) {
        print("******************OUTER******************");
        std::cout << "****************** "<< piece << " " << value[i][0] << " " << value[i][1] << "******************" << std::endl;
      }
      #ifdef DEBUGAI
      Log << "******************OUTER******************" << std::endl;
      Log << "****************** "<< piece << " " << value[i][0] << " " << value[i][1] << "******************" << std::endl;
      Black::print_blocks_Log();
      White::print_blocks_Log();
      #endif
      score = minimax(Black::depth, -10000, 10000, "W");
      scores.push_back(score);
      if (verbose) std::cout << piece << " (" << value[i][0] << " " << value[i][1] << ") " << score << std::endl;
      Board.pop();
      if (score >= std::stof(best_move["score"])) {
        best_move["score"] = str(score);
        best_move["piece"] = piece;
        best_move["pos"] = str(value[i][0]) + str(value[i][1]);
        std::cout << best_move["score"] << std::endl;
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
  std::cout << "Best move is " << best_move["piece"] << " to " << "(" << best_move["pos"][0] << ", " << best_move["pos"][1] << ")" << std::endl;
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
  // get a sorted list of all our scores to make sure we have the right move
  sort(scores.begin(), scores.end());
  if (verbose) {
    std::cout << "**Scores**" << std::endl;
    for (int i=0;i<scores.size();i++) {
      std::cout << scores[i] << std::endl;
    }
  }
  std::cout << "Obtained highest score of " << best_move["score"] << std::endl;
}

static double minimax(int n, double alpha, double beta, std::string player) {
  std::map<std::string, std::vector<std::vector<int>>> black_moves = Black::get_moves();
  std::map<std::string, std::vector<std::vector<int>>> white_moves = White::get_moves();
  std::map<std::string, std::vector<std::vector<int>>> btemp = black_moves;
  std::map<std::string, std::vector<std::vector<int>>> wtemp = white_moves;
  double best_move;
  if (n == 0)
    return -evaluate_pos();
  // minimizing player
  if (player == "B") {
    best_move = -9999;
    for (std::map<std::string, std::vector<std::vector<int>>>::iterator itr=btemp.begin();itr!=btemp.end();itr++) {
      std::string piece = random_key(black_moves);
      std::vector<std::vector<int>> value = black_moves[piece];
      for (int i=0;i<value.size();i++) {
        if (piece == "CK" || piece == "CQ") continue;
        Black::move_piece(piece, value[i][0], value[i][1]);
        if (verbose2) {
          print("INNER BLACK");
          std::cout << piece << " " << value[i][0] << " " << value[i][1] << std::endl;
        }
        #ifdef DEBUGAI
        Log << "INNER BLACK" << std::endl;
        Log << piece << " " << value[i][0] << " " << value[i][1] << std::endl;
        #endif
        best_move = std::max(best_move, minimax(n-1, alpha, beta, "W"));
        Board.pop();
        alpha = std::max(alpha, best_move);
        if (alpha >= beta)
          return best_move;
      }
      black_moves.erase(piece);
    }
  }
  // maximizing player
  else {
    best_move = 9999;
    for (std::map<std::string, std::vector<std::vector<int>>>::iterator itr=wtemp.begin();itr!=wtemp.end();itr++) {
      std::string piece = random_key(white_moves);
      std::vector<std::vector<int>> value = white_moves[piece];
      for (int i=0;i<value.size();i++) {
        White::move_piece(piece, value[i][0], value[i][1]);
        if (verbose2) {
          print("INNER WHITE");
          std::cout << piece << " " << value[i][0] << " " << value[i][1] << std::endl;
        }
        #ifdef DEBUGAI
        Log << "INNER WHITE" << std::endl;
        Log << piece << " " << value[i][0] << " " << value[i][1] << std::endl;
        #endif
        best_move = std::min(best_move, minimax(n-1, alpha, beta, "B"));
        Board.pop();
        beta = std::min(beta, best_move);
        if (alpha >= beta)
          return best_move;
      }
      white_moves.erase(piece);
    }
  }
  return best_move;
}
} // namespace Black::AI
