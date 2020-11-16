#include "../common.h"

namespace Black { namespace AI {

#define RBQ_OPEN_FILES_REWARD 0.025
#define BISHOP_PAIR_REWARD 1.4
#define PROMOTION_REWARD 10
#define PASSED_PAWN_REWARD 1.1

std::string random_key(std::map<std::string, std::vector<std::vector<int>>> m) {
  auto it = m.begin();
  std::advance(it, rand() % m.size());
  std::string key = it->first;
  return key;
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
  score -= RBQ_open_files();
  score -= pawn_promote();
  score -= passed_pawns();
  score -= bishop_pair();
  return score;
}

std::map<std::string, std::vector<std::vector<int>>> get_white_moves() {
  std::map<std::string, std::vector<std::vector<int>>> moves = {};
  if (White::King.alive && !White::King.movelist.empty())
    moves["K"] = White::King.movelist;
  for (int i=0;i<White::num_queens;i++) {
    if (White::Queen.alive[i] && !White::Queen.movelist[i].empty())
      moves["Q" + str(i)] = White::Queen.movelist[i];
  }
  for (int i=0;i<8;i++) {
    if (White::Pawn.alive[i] && !White::Pawn.movelist[i].empty())
      moves["P" + str(i)] = White::Pawn.movelist[i];
  }
  for (int i=0;i<2;i++) {
    if (White::Bishop.alive[i] && !White::Bishop.movelist[i].empty())
      moves["B" + str(i)] = White::Bishop.movelist[i];
    if (White::Knight.alive[i] && !White::Knight.movelist[i].empty())
      moves["N" + str(i)] = White::Knight.movelist[i];
    if (White::Rook.alive[i] && !White::Rook.movelist[i].empty())
      moves["R" + str(i)] = White::Rook.movelist[i];
  }
  return moves;
}

std::map<std::string, std::vector<std::vector<int>>> get_black_moves() {
  std::map<std::string, std::vector<std::vector<int>>> moves = {};
  if (Black::King.alive && !Black::King.movelist.empty())
    moves["K"] = Black::King.movelist;
  for (int i=0;i<Black::num_queens;i++) {
    if (Black::Queen.alive[i] && !Black::Queen.movelist[i].empty())
      moves["Q" + str(i)] = Black::Queen.movelist[i];
  }
  for (int i=0;i<8;i++) {
    if (Black::Pawn.alive[i] && !Black::Pawn.movelist[i].empty())
      moves["P" + str(i)] = Black::Pawn.movelist[i];
  }
  for (int i=0;i<2;i++) {
    if (Black::Bishop.alive[i] && !Black::Bishop.movelist[i].empty())
      moves["B" + str(i)] = Black::Bishop.movelist[i];
    if (Black::Knight.alive[i] && !Black::Knight.movelist[i].empty())
      moves["N" + str(i)] = Black::Knight.movelist[i];
    if (Black::Rook.alive[i] && !Black::Rook.movelist[i].empty())
      moves["R" + str(i)] = Black::Rook.movelist[i];
  }
  return moves;
}

} // namespace AI
} // namespace Black
