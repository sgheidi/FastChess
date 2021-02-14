#ifndef CORE_BLACK__H
#define CORE_BLACK__H

namespace Black {
extern std::vector<std::vector<int>> blocks;
extern bool turn;
extern int num_queens;
extern std::vector<std::string> checker;
extern std::vector<bool> en_passant;
extern const int depth;
extern bool screenshot;

std::map<std::string, std::vector<std::vector<int>>> get_moves();
void check_capture_screen();
void handle_undo_promotion(int i, int row, int col);
void revive(std::string piece, int row, int col);
void valid_move(bool is_undo, bool killed, std::string piece, int row, int col);
bool castle_criteria_K();
void castle_K(bool is_undo);
bool castle_criteria_Q();
void castle_Q(bool is_undo);
void reset_enpassant();
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

#endif // CORE_BLACK__H
