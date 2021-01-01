#ifndef WHITE__H
#define WHITE__H

namespace White {
extern std::vector<std::vector<int>> blocks;
extern int num_queens;
extern std::vector<std::string> checker;
extern std::vector<bool> en_passant;
extern bool turn;
extern bool enpassant_check_killed;
extern bool screenshot;

std::map<std::string, std::vector<std::vector<int>>> get_moves();
std::vector<std::string> get_movesVec();
void check_capture_screen();
static void pop_last_queen();
void handle_undo_promotion(int i, int row, int col);
void revive(std::string piece, int row, int col);
void reset_enpassant();
void valid_move(bool is_undo, bool killed, std::string piece, int row, int col);
bool castle_criteria_K();
void castle_K(bool is_undo);
bool castle_criteria_Q();
void castle_Q(bool is_undo);
static bool in_opp_movelist(int row, int col);
static bool opp_no_moves();
static void check_avoid_move();
static void check_pin();
static void update_opp_movelists();
static bool check_opp_checked();
static void promote(int i, int row_, int col_);
void kill(bool is_undo, std::string piece, int row, int col);
void move_piece(std::string piece, int row, int col);
static void check_kill(bool is_undo, int row, int col);
void move_piece(std::string piece, int row, int col);
std::string get_piece(int row_, int col_);
void play();
void print_blocks();
#ifdef DEBUGAI
void print_blocks_Log();
#endif
void show();
void init();

} // namespace White

#endif // WHITE__H
