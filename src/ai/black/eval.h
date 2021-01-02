#ifndef AI_BLACK_EVAL_H
#define AI_BLACK_EVAL_H

namespace Black::Eval {
double mobility();
double pawn_promote();
double bishop_pair();
double RBQ_open_files();
} // namespace Black::Eval

#endif // AI_BLACK_EVAL_H
