#ifndef HELPER_H
#define HELPER_H

namespace Black { namespace AI {
std::string random_key(std::map<std::string, std::vector<std::vector<int>>> m);
int evaluate_pos();
std::map<std::string, std::vector<std::vector<int>>> get_white_moves();
std::map<std::string, std::vector<std::vector<int>>> get_black_moves();
} // namespace AI
} // namespace Black

#endif // HELPER_H
