#ifndef HELPER_H
#define HELPER_H

namespace Black { namespace AI {
std::string random_key(std::map<std::string, std::vector<std::vector<int>>> m);
std::map<std::string, std::vector<std::vector<int>>> get_white_moves();
std::map<std::string, std::vector<std::vector<int>>> get_black_moves();
double RBQ_open_files();
double evaluate_pos();
double passed_pawns();
double pawn_promote();
double bishop_pair();
} // namespace AI
} // namespace Black

#endif // HELPER_H
