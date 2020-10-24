#ifndef BLACK_H
#define BLACK_H

namespace AI {
void gen_move();
std::map<std::string, std::vector<std::vector<int>>> find_best_move();
int minimax(int n, int alpha, int beta, std::string player);
}

#endif // BLACK_H
