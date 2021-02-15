#ifndef AI_BLACK_EVAL_H
#define AI_BLACK_EVAL_H

namespace black::eval {
double mobility();
double pawn_promote();
double bishop_pair();
double RBQ_open_files();
} // namespace black::eval

#endif // AI_BLACK_EVAL_H
