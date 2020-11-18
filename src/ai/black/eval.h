#ifndef BLACK_EVAL_H
#define BLACK_EVAL_H

namespace Black::Eval {
double mobility();
double N_attacked_defended();
double passed_pawns();
double pawn_promote();
double bishop_pair();
double RBQ_open_files();
} // namespace Black::Eval

#endif // BLACK_EVAL_H
