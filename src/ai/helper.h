#ifndef HELPER_H
#define HELPER_H

namespace AI {
int evaluate_pos();
std::map<std::string, std::vector<std::vector<int>>> get_white_moves();
std::map<std::string, std::vector<std::vector<int>>> get_black_moves();
}

#endif // HELPER_H
