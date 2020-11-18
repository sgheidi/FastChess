#include "../../common.h"

namespace Black::Eval {

// General mobility: the number of open positions available to each piece (non-BRQ).
double mobility() {
  double reward = 0;
  for (int i=0;i<8;i++) {
    if (Pawn.alive[i]) {
      for (int k=0;k<Pawn.movelist[i].size();k++) {
        if (!blocks[Pawn.movelist[i][k][0]][Pawn.movelist[i][k][1]] &&
        !White::blocks[Pawn.movelist[i][k][0]][Pawn.movelist[i][k][1]])
          reward += MOBILITY;
      }
    }
  }
  for (int i=0;i<2;i++) {
    if (Knight.alive[i]) {
      for (int k=0;k<Knight.movelist[i].size();k++) {
        reward += MOBILITY;
      }
    }
  }
  return reward;
}

// N points for every piece opposite piece that is attacked and not defended (N for piece value).
// - e.g white bishop attacked 3 times, defended 2 times -> N = 3.
// - e.g Black (AI) bishop attacked 3 times and defended 2 times -> N = -3.
// Do not consider defending more than needed (i.e only want defending at most N times for attacked N times).
double N_attacked_defended() {

}

double passed_pawns() {
  double reward = 0;
  for (int i=0;i<8;i++) {
    if (Pawn.row[i] >= 4)
      reward += PASSED_PAWN_REWARD;
    if (Pawn.row[i] >= 5)
      reward += 0.5;
    if (Pawn.row[i] >= 6)
      reward += 1.0;
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
