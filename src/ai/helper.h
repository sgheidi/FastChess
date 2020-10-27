#ifndef HELPER_H
#define HELPER_H

namespace Black { namespace AI {
std::map<std::string, std::vector<std::vector<int>>>
shuffle(std::map<std::string, std::vector<std::vector<int>>>)
int evaluate_pos();
std::map<std::string, std::vector<std::vector<int>>> get_white_moves();
std::map<std::string, std::vector<std::vector<int>>> get_black_moves();
} // namespace AI
} // namespace Black

#endif // HELPER_H
