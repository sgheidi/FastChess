#include "../../common.h"

namespace Black::Eval {

// General mobility: the number of open positions available to non-BRQ each piece.
double mobility() {
  double reward = 0;
  for (int i=0;i<2;i++) {
    if (Knight.alive[i]) {
      for (int k=0;k<Knight.movelist[i].size();k++)
        reward += MOBILITY;
    }
    if (Bishop.alive[i]) {
      for (int k=0;k<Bishop.movelist[i].size();k++)
        reward += MOBILITY;
    }
    if (Rook.alive[i]) {
      for (int k=0;k<Rook.movelist[i].size();k++)
        reward += MOBILITY;
    }
  }
  for (int i=0;i<num_queens;i++) {
    for (int k=0;k<Queen.movelist[i].size();k++)
      reward += MOBILITY;
  }
  return reward;
}

double pawn_promote() {
  double reward = 0;
  for (int i=0;i<8;i++) {
    if (Pawn.row[i] >= 7)
      reward += 10.0;
  }
  return reward;
}

double bishop_pair() {
  double reward = 0;
  if (Bishop.alive[0] && Bishop.alive[1])
    reward += BISHOP_PAIR_REWARD;
  return reward;
}

// RBQ reward for having 'open' movelists. That is, positions where no piece is placed.
double RBQ_open_files() {
  double reward = 0;
  for (int i=0;i<num_queens;i++) {
    if (Queen.alive[i]) {
      for (int k=0;k<Queen.movelist[i].size();k++) {
        if (!blocks[Queen.movelist[i][k][0]][Queen.movelist[i][k][1]] &&
        !White::blocks[Queen.movelist[i][k][0]][Queen.movelist[i][k][1]])
          reward += RBQ_OPEN_FILES_REWARD;
      }
    }
  }
  for (int i=0;i<2;i++) {
    if (Bishop.alive[i]) {
      for (int k=0;k<Bishop.movelist[i].size();k++) {
        if (!blocks[Bishop.movelist[i][k][0]][Bishop.movelist[i][k][1]] &&
        !White::blocks[Bishop.movelist[i][k][0]][Bishop.movelist[i][k][1]])
          reward += RBQ_OPEN_FILES_REWARD;
      }
    }
    if (Rook.alive[i]) {
      for (int k=0;k<Rook.movelist[i].size();k++) {
        if (!blocks[Rook.movelist[i][k][0]][Rook.movelist[i][k][1]] &&
        !White::blocks[Rook.movelist[i][k][0]][Rook.movelist[i][k][1]])
          reward += RBQ_OPEN_FILES_REWARD;
      }
    }
  }
  return reward;
}
} // namespace Black::Eval
