#ifndef AI_WHITE_EVAL_H
#define AI_WHITE_EVAL_H

namespace white {
namespace eval {
double mobility();
double N_attacked_defended();
double passed_pawns();
double pawn_promote();
double bishop_pair();
double RBQ_open_files();
} // namespace eval
} // namespace white

#endif // AI_WHITE_EVAL_H
