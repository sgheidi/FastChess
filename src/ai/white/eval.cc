#include "../../common/config.h"

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
#include "eval.h"

namespace white::eval {

// General mobility: the number of open positions available to each piece (non-BRQ).
double mobility() {
  double reward = 0;
  for (int i=0;i<2;i++) {
    if (knight.alive[i]) {
      for (int k=0;k<knight.movelist[i].size();k++) {
        reward += MOBILITY;
      }
    }
    if (bishop.alive[i]) {
      for (int k=0;k<bishop.movelist[i].size();k++) {
        reward += MOBILITY;
      }
    }
    if (rook.alive[i]) {
      for (int k=0;k<rook.movelist[i].size();k++) {
        reward += MOBILITY;
      }
    }
  }
  for (int i=0;i<num_queens;i++) {
    for (int k=0;k<queen.movelist[i].size();k++) {
      reward += MOBILITY;
    }
  }
  return reward;
}

double passed_pawns() {
  double reward = 0;
  for (int i=0;i<8;i++) {
    if (pawn.row[i] >= 4)
      reward += PASSED_PAWNS[0];
    if (pawn.row[i] >= 5)
      reward += PASSED_PAWNS[1];
    if (pawn.row[i] >= 6)
      reward += PASSED_PAWNS[2];
  }
  return reward;
}

double pawn_promote() {
  double reward = 0;
  for (int i=0;i<8;i++) {
    if (pawn.row[i] >= 7)
      reward += 10.0;
  }
  return reward;
}

double bishop_pair() {
  double reward = 0;
  if (bishop.alive[0] && bishop.alive[1])
    reward += BISHOP_PAIR_REWARD;
  return reward;
}

// RBQ reward for having 'open' movelists. That is, positions where no piece is placed.
double RBQ_open_files() {
  double reward = 0;
  for (int i=0;i<num_queens;i++) {
    if (queen.alive[i]) {
      for (int k=0;k<queen.movelist[i].size();k++) {
        if (!blocks[queen.movelist[i][k][0]][queen.movelist[i][k][1]] && !black::blocks[queen.movelist[i][k][0]][queen.movelist[i][k][1]])
          reward += RBQ_OPEN_FILES_REWARD;
      }
    }
  }
  for (int i=0;i<2;i++) {
    if (bishop.alive[i]) {
      for (int k=0;k<bishop.movelist[i].size();k++) {
        if (!blocks[bishop.movelist[i][k][0]][bishop.movelist[i][k][1]] && !black::blocks[bishop.movelist[i][k][0]][bishop.movelist[i][k][1]])
          reward += RBQ_OPEN_FILES_REWARD;
      }
    }
    if (rook.alive[i]) {
      for (int k=0;k<rook.movelist[i].size();k++) {
        if (!blocks[rook.movelist[i][k][0]][rook.movelist[i][k][1]] && !black::blocks[rook.movelist[i][k][0]][rook.movelist[i][k][1]])
          reward += RBQ_OPEN_FILES_REWARD;
      }
    }
  }
  return reward;
}
} // namespace white::eval
