#ifndef HELPER_H
#define HELPER_H

#define MOBILITY 0.15
#define RBQ_OPEN_FILES_REWARD 0.025
#define BISHOP_PAIR_REWARD 1.4
#define PROMOTION_REWARD 10
#define PASSED_PAWN_REWARD 1.1

namespace Black::AI {
std::string random_key(std::map<std::string, std::vector<std::vector<int>>> m);
std::map<std::string, std::vector<std::vector<int>>> get_white_moves();
std::map<std::string, std::vector<std::vector<int>>> get_black_moves();
double RBQ_open_files();
double evaluate_pos();
double passed_pawns();
double pawn_promote();
double bishop_pair();
} // namespace Black::AI

#endif // HELPER_H
