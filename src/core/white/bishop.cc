#include "../../common/config.h"
#include "../../common/util.h"

#include "../../board.h"

#include "../black/bishop.h"
#include "../black/knight.h"
#include "../black/pawn.h"
#include "../black/rook.h"
#include "../black/queen.h"
#include "../black/king.h"

#include "bishop.h"

#include "../white_.h"
#include "../black_.h"

namespace white {

void Bishop_Piece::pure_move(int i, int row_, int col_) {
  blocks[row_][col_] = 1;
  row[i] = row_;
  col[i] = col_;
  x[i] = col[i]*UNIT;
  y[i] = row[i]*UNIT;
}

void Bishop_Piece::pin(int k, std::string piece) {
  const std::vector<std::vector<int>> pinned_movelist = get_check_movelist(k);
  for (int i=0;i<black::num_queens;i++) {
    if (piece == "Q" + std::to_string(i))
      filter(black::queen.movelist[i], pinned_movelist);
  }
  for (int i=0;i<2;i++) {
    if (piece == "B" + std::to_string(i))
      filter(black::bishop.movelist[i], pinned_movelist);
    else if (piece == "N" + std::to_string(i))
      filter(black::knight.movelist[i], pinned_movelist);
    else if (piece == "R" + std::to_string(i))
      filter(black::rook.movelist[i], pinned_movelist);
  }
  for (int i=0;i<8;i++) {
    if (piece == "P" + std::to_string(i))
      filter(black::pawn.movelist[i], pinned_movelist);
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
  const std::vector<int> pos = {black::king.row, black::king.col};
  int row_;
  int col_;
  if (pos[0] > row[i] && pos[1] > col[i]) {
    row_ = row[i]+1;
    col_ = col[i]+1;
    while (pos[0] > row_) {
      if (black::blocks[row_][col_])
        return black::get_piece(row_, col_);
      row_ ++;
      col_ ++;
    }
  }
  else if (pos[0] > row[i] && pos[1] < col[i]) {
    row_ = row[i]+1;
    col_ = col[i]-1;
    while (pos[0] > row_) {
      if (black::blocks[row_][col_])
        return black::get_piece(row_, col_);
      row_ ++;
      col_ --;
    }
  }
  else if (pos[0] < row[i] && pos[1] > col[i]) {
    row_ = row[i]-1;
    col_ = col[i]+1;
    while (pos[0] < row_) {
      if (black::blocks[row_][col_])
        return black::get_piece(row_, col_);
      row_ --;
      col_ ++;
    }
  }
  else if (pos[0] < row[i] && pos[1] < col[i]) {
    row_ = row[i]-1;
    col_ = col[i]-1;
    while (pos[0] < row_) {
      if (black::blocks[row_][col_]) {
        return black::get_piece(row_, col_);
      }
      row_ --;
      col_ --;
    }
  }
}

int Bishop_Piece::num_pieces(int i) {
  const std::vector<int> pos = {black::king.row, black::king.col};
  int row_;
  int col_;
  int total = 0;
  if (pos[0] > row[i] && pos[1] > col[i]) {
    row_ = row[i]+1;
    col_ = col[i]+1;
    while (pos[0] > row_) {
      if (black::blocks[row_][col_])
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
      if (black::blocks[row_][col_])
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
      if (black::blocks[row_][col_])
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
      if (black::blocks[row_][col_])
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
  const std::vector<int> pos = {black::king.row, black::king.col};
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

std::vector<int> Bishop_Piece::get_avoid_move(int i) {
  const std::vector<int> pos = {black::king.row, black::king.col};
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

std::vector<std::vector<int>> Bishop_Piece::get_check_movelist(int i) {
  const std::vector<int> pos = {black::king.row, black::king.col};
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
      if (black::blocks[row_][col_])
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
      if (black::blocks[row_][col_])
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
      if (black::blocks[row_][col_])
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
      if (black::blocks[row_][col_])
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
    if (!texture.loadFromFile("assets/sprites/whitebishop.png"))
      return;
    sprite.setTexture(texture);
    sprite.setScale(board.pieces_scale, board.pieces_scale);
    sprite.setPosition(x[i] + board.pieces_paddingx, y[i] + board.pieces_paddingy);
    window.draw(sprite);
  }
}

} // namespace white
