#ifndef WHITE_EVAL_H
#define WHITE_EVAL_H

namespace White::Eval {
double mobility();
double N_attacked_defended();
double passed_pawns();
double pawn_promote();
double bishop_pair();
double RBQ_open_files();
} // namespace White::Eval

#endif // WHITE_EVAL_H
