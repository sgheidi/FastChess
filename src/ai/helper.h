#ifndef AI_HELPER_H
#define AI_HELPER_H

#define MOBILITY 0.085
#define RBQ_OPEN_FILES_REWARD 0.025
#define BISHOP_PAIR_REWARD 1.4
#define PROMOTION_REWARD 10.0

extern const std::vector<double> PASSED_PAWNS;
extern const std::vector<double> CONNECTED_PASSED_PAWNS;
extern const std::vector<double> PROTECTED_PASSED_PAWNS;

namespace Black::AI {
std::string random_key(std::map<std::string, std::vector<std::vector<int>>> m);
double RBQ_open_files();
double evaluate_pos();
double passed_pawns();
double pawn_promote();
double bishop_pair();
} // namespace Black::AI

#endif // AI_HELPER_H
