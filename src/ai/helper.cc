#include "../common/config.h"

#include "../core/black/bishop.h"
#include "../core/black/knight.h"
#include "../core/black/pawn.h"
#include "../core/black/rook.h"
#include "../core/black/queen.h"
#include "../core/black/king.h"

#include "../core/white/bishop.h"
#include "../core/white/knight.h"
#include "../core/white/pawn.h"
#include "../core/white/rook.h"
#include "../core/white/queen.h"
#include "../core/white/king.h"

#include "../core/white_.h"
#include "../core/black_.h"

#include "helper.h"
#include "black/eval.h"
#include "white/eval.h"

// ranks 4, 5, 6. These rewards accumulate as a pawn advances in its file.
const std::vector<double> PASSED_PAWNS = {1.1, 0.5, 0.5};

// Very high reward for connected passed pawns as they will queen soon.
const std::vector<double> CONNECTED_PASSED_PAWNS = {0.5, 1.0, 2.0};
const std::vector<double> PROTECTED_PASSED_PAWNS = {0.2, 0.5, 0.6};

namespace black::ai {
std::string random_key(const std::map<std::string, std::vector<std::vector<int>>>& m) {
  auto it = m.begin();
  std::advance(it, rand() % m.size());
  std::string key = it->first;
  return key;
}

double evaluate_pos() {
  double score = 0;
  if (black::king.alive)
    score -= 2;
  for (int i=0;i<black::num_queens;i++) {
    if (black::queen.alive[i])
      score -= 9;
  }
  for (int i=0;i<8;i++) {
    if (black::pawn.alive[i])
      score -= 1;
  }
  for (int i=0;i<2;i++) {
    if (black::bishop.alive[i])
      score -= 3;
    if (black::knight.alive[i])
      score -= 3;
    if (black::rook.alive[i])
      score -= 5;
  }
  if (white::king.alive)
    score += 2;
  for (int i=0;i<white::num_queens;i++) {
    if (white::queen.alive[i])
      score += 9;
  }
  for (int i=0;i<8;i++) {
    if (white::pawn.alive[i])
      score += 1;
  }
  for (int i=0;i<2;i++) {
    if (white::bishop.alive[i])
      score += 3;
    if (white::knight.alive[i])
      score += 3;
    if (white::rook.alive[i])
      score += 5;
  }
  // score -= Eval::RBQ_open_files();
  // score -= Eval::pawn_promote();
  // score -= Eval::passed_pawns();
  // score -= Eval::bishop_pair();
  score -= Eval::mobility();
  // score += white::eval::RBQ_open_files();
  // score += white::eval::pawn_promote();
  // score += white::eval::passed_pawns();
  // score += white::eval::bishop_pair();
  score += white::eval::mobility();
  return score;
}
} // namespace black::ai
