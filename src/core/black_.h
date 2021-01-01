#ifndef BLACK__H
#define BLACK__H

namespace Black {
extern std::vector<std::vector<int>> blocks;
extern bool turn;
extern int num_queens;
extern std::vector<std::string> checker;
extern std::vector<bool> en_passant;
extern const bool is_AI;
extern const int depth;
extern bool screenshot;

std::map<std::string, std::vector<std::vector<int>>> get_moves();
std::vector<std::string> get_movesVec();
void check_capture_screen();
static void pop_last_queen();
void handle_undo_promotion(int i, int row, int col);
void revive(std::string piece, int row, int col);
static bool opp_no_moves();
void valid_move(bool is_undo, bool killed, std::string piece, int row, int col);
bool castle_criteria_K();
void castle_K(bool is_undo);
bool castle_criteria_Q();
void castle_Q(bool is_undo);
static bool in_opp_movelist(int row, int col);
void reset_enpassant();
static void check_pin();
static void check_avoid_move();
static void update_opp_movelists();
static bool check_opp_checked();
static void promote(int i, int row_, int col_);
static void check_kill(bool is_undo, int row, int col);
void kill(bool is_undo, std::string piece, int row, int col);
void move_piece(std::string piece, int row, int col);
std::string get_piece(int row_, int col_);
void play();
void print_blocks();
#ifdef DEBUGAI
void print_blocks_Log();
#endif
void show();
void init();

} // namespace Black

#endif // BLACK__H
