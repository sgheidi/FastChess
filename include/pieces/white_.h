#ifndef WHITE__H
#define WHITE__H

namespace White {
extern Bishop_Piece Bishop;
extern Knight_Piece Knight;
extern Pawn_Piece Pawn;
extern Rook_Piece Rook;
extern King_Piece King;
extern Queen_Piece Queen;
extern std::vector<std::vector<int>> blocks;
extern bool turn;
extern int num_queens;

void update_opp_movelists();
bool check_opp_checked();
void promote(int i);
void kill(std::string piece);
void move_piece(std::string piece, int row, int col);
void check_kill(int row, int col);
void move_piece(std::string piece, int row, int col);
std::string get_piece(int row_, int col_);
void play();
void print_blocks();
void show();
void init();

} // namespace White

#endif // WHITE__H
