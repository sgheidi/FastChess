#ifndef BLACK_SEARCH_H
#define BLACK_SEARCH_H

namespace Black::AI {
void gen_move();
static double minimax(int n, double alpha, double beta, std::string player);
} // namespace Black::AI

#endif // BLACK_SEARCH_H
