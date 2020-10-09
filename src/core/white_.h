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
extern std::vector<std::string> checker;
extern std::vector<bool> en_passant;

void pop_last_queen();
void handle_undo_promotion(int i, int row, int col);
void revive(std::string piece, int row, int col);
void reset_opp_enpassant();
void valid_move(bool is_undo, bool killed, std::string piece, int row, int col);
bool castle_criteria_K();
void castle_K(bool is_undo);
bool castle_criteria_Q();
void castle_Q(bool is_undo);
bool in_opp_movelist(int row, int col);
bool opp_no_moves();
void check_avoid_move();
void check_pin();
void update_opp_movelists();
bool check_opp_checked();
void promote(int i, int row_, int col_);
void kill(bool is_undo, std::string piece, int row, int col);
void move_piece(std::string piece, int row, int col);
void check_kill(bool is_undo, int row, int col);
void move_piece(std::string piece, int row, int col);
std::string get_piece(int row_, int col_);
void play();
void print_blocks();
void show();
void init();

} // namespace White

#endif // WHITE__H
