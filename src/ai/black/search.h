#ifndef BLACK_SEARCH_H
#define BLACK_SEARCH_H

namespace Black::AI {
void gen_move();
std::map<std::string, std::vector<std::vector<int>>> find_best_move();
int minimax(int n, int alpha, int beta, std::string player);
} // namespace Black::AI

#endif // BLACK_SEARCH_H
