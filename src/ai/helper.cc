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

namespace Black::AI {
std::string random_key(const std::map<std::string, std::vector<std::vector<int>>>& m) {
  auto it = m.begin();
  std::advance(it, rand() % m.size());
  std::string key = it->first;
  return key;
}

double evaluate_pos() {
  double score = 0;
  if (Black::King.alive)
    score -= 2;
  for (int i=0;i<Black::num_queens;i++) {
    if (Black::Queen.alive[i])
      score -= 9;
  }
  for (int i=0;i<8;i++) {
    if (Black::Pawn.alive[i])
      score -= 1;
  }
  for (int i=0;i<2;i++) {
    if (Black::Bishop.alive[i])
      score -= 3;
    if (Black::Knight.alive[i])
      score -= 3;
    if (Black::Rook.alive[i])
      score -= 5;
  }
  if (White::King.alive)
    score += 2;
  for (int i=0;i<White::num_queens;i++) {
    if (White::Queen.alive[i])
      score += 9;
  }
  for (int i=0;i<8;i++) {
    if (White::Pawn.alive[i])
      score += 1;
  }
  for (int i=0;i<2;i++) {
    if (White::Bishop.alive[i])
      score += 3;
    if (White::Knight.alive[i])
      score += 3;
    if (White::Rook.alive[i])
      score += 5;
  }
  // score -= Eval::RBQ_open_files();
  // score -= Eval::pawn_promote();
  // score -= Eval::passed_pawns();
  // score -= Eval::bishop_pair();
  score -= Eval::mobility();
  // score += White::Eval::RBQ_open_files();
  // score += White::Eval::pawn_promote();
  // score += White::Eval::passed_pawns();
  // score += White::Eval::bishop_pair();
  score += White::Eval::mobility();
  return score;
}
} // namespace Black::AI
