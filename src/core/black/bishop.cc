#include "../../common/config.h"
#include "../../common/util.h"

#include "../../board.h"

#include "../white/bishop.h"
#include "../white/knight.h"
#include "../white/pawn.h"
#include "../white/rook.h"
#include "../white/queen.h"
#include "../white/king.h"

#include "bishop.h"

#include "../white_.h"
#include "../black_.h"

namespace Black {

void Bishop_Piece::pure_move(int i, int row_, int col_) {
  blocks[row_][col_] = 1;
  row[i] = row_;
  col[i] = col_;
  x[i] = col[i]*UNIT;
  y[i] = row[i]*UNIT;
}

void Bishop_Piece::pin(int k, std::string piece) {
  std::vector<std::vector<int>> pinned_movelist = get_check_movelist(k);
  for (int i=0;i<White::num_queens;i++) {
    if (piece == "Q" + std::to_string(i))
      White::Queen.movelist[i] = filter(White::Queen.movelist[i], pinned_movelist);
  }
  for (int i=0;i<2;i++) {
    if (piece == "B" + std::to_string(i))
      White::Bishop.movelist[i] = filter(White::Bishop.movelist[i], pinned_movelist);
    else if (piece == "N" + std::to_string(i))
      White::Knight.movelist[i] = filter(White::Knight.movelist[i], pinned_movelist);
    else if (piece == "R" + std::to_string(i))
      White::Rook.movelist[i] = filter(White::Rook.movelist[i], pinned_movelist);
  }
  for (int i=0;i<8;i++) {
    if (piece == "P" + std::to_string(i))
      White::Pawn.movelist[i] = filter(White::Pawn.movelist[i], pinned_movelist);
  }
}

void Bishop_Piece::check_pin() {
  for (int i=0;i<2;i++) {
    if (alive[i]) {
      if (king_in_path(i) && num_pieces(i) == 1)
        pin(i, get_pinned_piece(i));
    }
  }
}

std::string Bishop_Piece::get_pinned_piece(int i) {
  std::vector<int> pos = {White::King.row, White::King.col};
  int row_;
  int col_;
  if (pos[0] > row[i] && pos[1] > col[i]) {
    row_ = row[i]+1;
    col_ = col[i]+1;
    while (pos[0] > row_) {
      if (White::blocks[row_][col_])
        return White::get_piece(row_, col_);
      row_ ++;
      col_ ++;
    }
  }
  else if (pos[0] > row[i] && pos[1] < col[i]) {
    row_ = row[i]+1;
    col_ = col[i]-1;
    while (pos[0] > row_) {
      if (White::blocks[row_][col_])
        return White::get_piece(row_, col_);
      row_ ++;
      col_ --;
    }
  }
  else if (pos[0] < row[i] && pos[1] > col[i]) {
    row_ = row[i]-1;
    col_ = col[i]+1;
    while (pos[0] < row_) {
      if (White::blocks[row_][col_])
        return White::get_piece(row_, col_);
      row_ --;
      col_ ++;
    }
  }
  else if (pos[0] < row[i] && pos[1] < col[i]) {
    row_ = row[i]-1;
    col_ = col[i]-1;
    while (pos[0] < row_) {
      if (White::blocks[row_][col_]) {
        return White::get_piece(row_, col_);
      }
      row_ --;
      col_ --;
    }
  }
}

int Bishop_Piece::num_pieces(int i) {
  std::vector<int> pos = {White::King.row, White::King.col};
  int row_;
  int col_;
  int total = 0;
  if (pos[0] > row[i] && pos[1] > col[i]) {
    row_ = row[i]+1;
    col_ = col[i]+1;
    while (pos[0] > row_) {
      if (White::blocks[row_][col_])
        total ++;
      else if (blocks[row_][col_])
        return 0;
      row_ ++;
      col_ ++;
    }
  }
  else if (pos[0] > row[i] && pos[1] < col[i]) {
    row_ = row[i]+1;
    col_ = col[i]-1;
    while (pos[0] > row_) {
      if (White::blocks[row_][col_])
        total ++;
      else if (blocks[row_][col_])
        return 0;
      row_ ++;
      col_ --;
    }
  }
  else if (pos[0] < row[i] && pos[1] < col[i]) {
    row_ = row[i]-1;
    col_ = col[i]-1;
    while (pos[0] < row_) {
      if (White::blocks[row_][col_])
        total ++;
      else if (blocks[row_][col_])
        return 0;
      row_ --;
      col_ --;
    }
  }
  else if (pos[0] < row[i] && pos[1] > col[i]) {
    row_ = row[i]-1;
    col_ = col[i]+1;
    while (pos[0] < row_) {
      if (White::blocks[row_][col_])
        total ++;
      else if (blocks[row_][col_])
        return 0;
      row_ --;
      col_ ++;
    }
  }
  return total;
}

bool Bishop_Piece::king_in_path(int i) {
  std::vector<int> pos = {White::King.row, White::King.col};
  int row_;
  int col_;
  row_ = row[i]+1;
  col_ = col[i]+1;
  while (row_ <= 7) {
    if (row_ == pos[0] && col_ == pos[1])
      return true;
    row_ ++;
    col_ ++;
  }
  row_ = row[i]+1;
  col_ = col[i]-1;
  while (row_ <= 7) {
    if (row_ == pos[0] && col_ == pos[1])
      return true;
    row_ ++;
    col_ --;
  }
  row_ = row[i]-1;
  col_ = col[i]-1;
  while (row_ >= 0) {
    if (row_ == pos[0] && col_ == pos[1])
      return true;
    row_ --;
    col_ --;
  }
  row_ = row[i]-1;
  col_ = col[i]+1;
  while (row_ >= 0) {
    if (row_ == pos[0] && col_ == pos[1])
      return true;
    row_ --;
    col_ ++;
  }
  return false;
}

std::vector<std::vector<int>> Bishop_Piece::get_check_movelist(int i) {
  std::vector<int> pos = {White::King.row, White::King.col};
  int row_;
  int col_;
  std::vector<std::vector<int>> ret;
  ret.push_back({row[i], col[i]});
  if (pos[0] > row[i] && pos[1] > col[i]) {
    row_ = row[i]+1;
    col_ = col[i]+1;
    while (pos[0] > row_) {
      ret.push_back({row_, col_});
      row_ ++;
      col_ ++;
    }
  }
  else if (pos[0] > row[i] && pos[1] < col[i]) {
    row_ = row[i]+1;
    col_ = col[i]-1;
    while (pos[0] > row_) {
      ret.push_back({row_, col_});
      row_ ++;
      col_ --;
    }
  }
  else if (pos[0] < row[i] && pos[1] > col[i]) {
    row_ = row[i]-1;
    col_ = col[i]+1;
    while (pos[0] < row_) {
      ret.push_back({row_, col_});
      row_ --;
      col_ ++;
    }
  }
  else if (pos[0] < row[i] && pos[1] < col[i]) {
    row_ = row[i]-1;
    col_ = col[i]-1;
    while (pos[0] < row_) {
      ret.push_back({row_, col_});
      row_ --;
      col_ --;
    }
  }
  return ret;
}

std::vector<int> Bishop_Piece::get_avoid_move(int i) {
  std::vector<int> pos = {White::King.row, White::King.col};
  std::vector<int> ret;
  if (pos[0] > row[i] && pos[1] > col[i])
    ret = {pos[0]+1, pos[1]+1};
  else if (pos[0] < row[i] && pos[1] > col[i])
    ret = {pos[0]-1, pos[1]+1};
  else if (pos[0] > row[i] && pos[1] < col[i])
    ret = {pos[0]+1, pos[1]-1};
  else if (pos[0] < row[i] && pos[1] < col[i])
    ret = {pos[0]-1, pos[1]-1};
  return ret;
}

void Bishop_Piece::update_movelist() {
  for (int i=0;i<2;i++) {
    if (!alive[i])
      continue;
    movelist[i].clear();
    protecting_movelist[i].clear();
    int row_ = row[i]+1;
    int col_ = col[i]+1;
    while (row_ <= 7 && col_ <= 7) {
      if (blocks[row_][col_]) {
        protecting_movelist[i].push_back({row_, col_});
        break;
      }
      movelist[i].push_back({row_, col_});
      if (White::blocks[row_][col_])
        break;
      row_ ++;
      col_ ++;
    }
    row_ = row[i]-1;
    col_ = col[i]+1;
    while (row_ >= 0 && col_ <= 7) {
      if (blocks[row_][col_]) {
        protecting_movelist[i].push_back({row_, col_});
        break;
      }
      movelist[i].push_back({row_, col_});
      if (White::blocks[row_][col_])
        break;
      row_ --;
      col_ ++;
    }
    row_ = row[i]+1;
    col_ = col[i]-1;
    while (row_ <= 7 && col_ >= 0) {
      if (blocks[row_][col_]) {
        protecting_movelist[i].push_back({row_, col_});
        break;
      }
      movelist[i].push_back({row_, col_});
      if (White::blocks[row_][col_])
        break;
      row_ ++;
      col_ --;
    }
    row_ = row[i]-1;
    col_ = col[i]-1;
    while (row_ >= 0 && col_ >= 0) {
      if (blocks[row_][col_]) {
        protecting_movelist[i].push_back({row_, col_});
        break;
      }
      movelist[i].push_back({row_, col_});
      if (White::blocks[row_][col_])
        break;
      row_ --;
      col_ --;
    }
  }
}

void Bishop_Piece::move(int i, int row_, int col_) {
  blocks[row[i]][col[i]] = 0;
  blocks[row_][col_] = 1;
  row[i] = row_;
  col[i] = col_;
  x[i] = col[i]*UNIT;
  y[i] = row[i]*UNIT;
}

void Bishop_Piece::show() {
  for (int i=0;i<2;i++) {
    if (!alive[i])
      continue;
    if (!texture.loadFromFile("assets/sprites/blackBishop.png"))
      return;
    sprite.setTexture(texture);
    sprite.setScale(Board.pieces_scale, Board.pieces_scale);
    sprite.setPosition(x[i] + Board.pieces_paddingx, y[i] + Board.pieces_paddingy);
    window.draw(sprite);
  }
}

} // namespace Black
