#include "../../common/config.h"
#include "../../common/util.h"
#include "../../board.h"
#include "../../core/black/rook.h"
#include "../../core/black/king.h"
#include "../../core/white/rook.h"
#include "../../core/white/king.h"
#include "../../core/white_.h"
#include "../../core/black_.h"
#include "../helper.h"
#include "../white/eval.h"
#include "eval.h"
#include "search.h"

namespace black {
namespace ai {

namespace {

constexpr int NEG_INF = -9999;
constexpr int POS_INF = 9999;

static const double minimax(const int& n, 
                            double alpha, 
                            double beta,
                            std::string player) {
  std::map<std::string, std::vector<std::vector<int>>> black_moves = black::get_moves();
  std::map<std::string, std::vector<std::vector<int>>> white_moves = white::get_moves();
  std::map<std::string, std::vector<std::vector<int>>> btemp = black_moves;
  std::map<std::string, std::vector<std::vector<int>>> wtemp = white_moves;
  double best_move;
  if (n == 0)
    return -evaluate_pos();
  // minimizing player
  if (player == "B") {
    best_move = NEG_INF;
    for (const auto& [k, v] : btemp) {
      std::string piece = random_key(black_moves);
      std::vector<std::vector<int>> value = black_moves[piece];
      for (int i=0;i<value.size();i++) {
        if (piece == "CK" || piece == "CQ") continue;
        black::move_piece(piece, value[i][0], value[i][1]);
        #ifdef VERBOSE2
          print("INNER BLACK");
          std::cout << piece << " " << value[i][0] << " " << value[i][1] << std::endl;
        #endif
        #ifdef DEBUGAI
          log << "INNER BLACK" << std::endl;
          log << piece << " " << value[i][0] << " " << value[i][1] << std::endl;
        #endif
        best_move = std::max(best_move, minimax(n-1, alpha, beta, "W"));
        board.pop();
        alpha = std::max(alpha, best_move);
        if (alpha >= beta)
          return best_move;
      }
      black_moves.erase(piece);
    }
  }
  // maximizing player
  else {
    best_move = POS_INF;
    for (const auto& [k, v] : wtemp) {
      std::string piece = random_key(white_moves);
      std::vector<std::vector<int>> value = white_moves[piece];
      for (int i=0;i<value.size();i++) {
        white::move_piece(piece, value[i][0], value[i][1]);
        #ifdef VERBOSE2
          print("INNER WHITE");
          std::cout << piece << " " << value[i][0] << " " << value[i][1] << std::endl;
        #endif
        #ifdef DEBUGAI
          log << "INNER WHITE" << std::endl;
          log << piece << " " << value[i][0] << " " << value[i][1] << std::endl;
        #endif
        best_move = std::min(best_move, minimax(n-1, alpha, beta, "B"));
        board.pop();
        beta = std::min(beta, best_move);
        if (alpha >= beta)
          return best_move;
      }
      white_moves.erase(piece);
    }
  }
  return best_move;
  }
} // namespace

void gen_move() {
  print("Generating move...");
  #ifdef DEBUGAI
    log << "Generating move..." << std::endl;
  #endif
  std::map<std::string, std::string> best_move = {{"score", "-9999"}, {"piece", ""}, {"pos", ""}};
  std::map<std::string, std::vector<std::vector<int>>> moves = black::get_moves();
  std::map<std::string, std::vector<std::vector<int>>> temp = moves;
  double score;
  board.isFrozen = true;
  const bool W_king_moved = white::king.moved;
  const std::vector<bool> W_rook_moved = {white::rook.moved[0], white::rook.moved[1]};
  const bool B_king_moved = black::king.moved;
  const std::vector<bool> B_rook_moved = {black::rook.moved[0], black::rook.moved[1]};
  std::vector<double> scores = {};
  for (const auto& [k, v] : temp) {
    std::string piece = random_key(moves);
    std::vector<std::vector<int>> value = moves[piece];
    for (int i=0;i<value.size();i++) {
      if (piece == "CK")
        black::castle_K(false);
      if (piece == "CQ")
        black::castle_Q(false);
      else
        black::move_piece(piece, value[i][0], value[i][1]);
      #ifdef VERBOSE2
        print("******************OUTER******************");
        std::cout << "****************** "<< piece << " " << value[i][0] << " " << value[i][1] << "******************" << std::endl;
      #endif
      #ifdef DEBUGAI
        log << "******************OUTER******************" << std::endl;
        log << "****************** "<< piece << " " << value[i][0] << " " << value[i][1] << "******************" << std::endl;
        black::print_blocks_log();
        white::print_blocks_log();
      #endif
      score = minimax(black::depth, -10000, 10000, "W");
      scores.push_back(score);
      #ifdef VERBOSE 
        std::cout << piece << " (" << value[i][0] << " " << value[i][1] << ") " << score << std::endl;
      #endif
      board.pop();
      if (score >= std::stof(best_move["score"])) {
        best_move["score"] = str(score);
        best_move["piece"] = piece;
        best_move["pos"] = str(value[i][0]) + str(value[i][1]);
        #ifdef VERBOSE
        std::cout << best_move["score"] << std::endl;
        #endif
      }
    }
    moves.erase(piece);
  }
  board.isFrozen = false;
  if (best_move["piece"] == "") {
    #ifdef DEBUGAI
      log << "No moves left!" << std::endl;
    #endif
    print("No moves left!");
    exit(1);
  }
  if (best_move["piece"] == "CK")
    black::castle_K(false);
  else if (best_move["piece"] == "CQ")
    black::castle_Q(false);
  else
    black::move_piece(best_move["piece"], best_move["pos"][0]-'0', best_move["pos"][1]-'0');
  #ifdef VERBOSE
  std::cout << "Best move is " << best_move["piece"] << " to " << "(" << best_move["pos"][0] << ", " 
  << best_move["pos"][1] << ")" << std::endl;
  #endif
  #ifndef IS_TESTING
    black::turn = false;
    white::turn = true;
  #endif
  white::rook.moved[0] = W_rook_moved[0];
  white::rook.moved[1] = W_rook_moved[1];
  black::rook.moved[0] = B_rook_moved[0];
  black::rook.moved[1] = B_rook_moved[1];
  white::king.moved = W_king_moved;
  black::king.moved = B_king_moved;
  // get a sorted list of all our scores to make sure we have the right move
  sort(scores.begin(), scores.end());
  #ifdef VERBOSE
    std::cout << "**Scores**" << std::endl;
    for (double s : scores)
      std::cout << s << std::endl;
  std::cout << "Obtained highest score of " << best_move["score"] << std::endl;
  #endif
}
} // namespace ai
} // namespace black
