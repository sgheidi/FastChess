#ifndef AI_HELPER_H
#define AI_HELPER_H

// pieces
#define P_REWARD 1
#define NB_REWARD 3
#define Q_REWARD 10
#define R_REWARD 9

// other
#define MOBILITY 0.085
#define RBQ_OPEN_FILES_REWARD 0.025
#define BISHOP_PAIR_REWARD 1.4
#define PROMOTION_REWARD 10.0

extern const std::vector<double> PASSED_PAWNS;
extern const std::vector<double> CONNECTED_PASSED_PAWNS;
extern const std::vector<double> PROTECTED_PASSED_PAWNS;

namespace black {
namespace ai {
std::string random_key(const std::map<std::string, std::vector<std::vector<int>>>& m);
double RBQ_open_files();
double evaluate_pos();
double passed_pawns();
double pawn_promote();
double bishop_pair();
} // namespace ai
} // namespace black

#endif // AI_HELPER_H
