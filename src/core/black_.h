#ifndef BLACK__H
#define BLACK__H

namespace Black {
extern Bishop_Piece Bishop;
extern Knight_Piece Knight;
extern Pawn_Piece Pawn;
extern Rook_Piece Rook;
extern King_Piece King;
extern Queen_Piece Queen;
extern std::vector<std::vector<int>> blocks;
extern bool turn;
extern int num_queens;
extern std::vector<std::string> checker;
extern std::vector<bool> en_passant;

bool opp_no_moves();
void valid_move(bool killed, std::string piece, int row, int col);
bool castle_criteria_K();
void castle_K();
bool castle_criteria_Q();
void castle_Q();
bool in_opp_movelist(int row, int col);
void reset_opp_enpassant();
void check_pin();
void check_avoid_move();
void update_opp_movelists();
bool check_opp_checked();
void promote(int i);
void check_kill(int row, int col);
void kill(std::string piece);
void move_piece(std::string piece, int row, int col);
std::string get_piece(int row_, int col_);
void play();
void print_blocks();
void show();
void init();

} // namespace Black

#endif // BLACK__H
