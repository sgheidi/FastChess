#include "../../../include/common.h"

namespace Black {

std::vector<std::vector<int>> Queen_Piece::get_check_movelist(int i) {
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
  else if (pos[0] > row[i]) {
    row_ = row[i]+1;
    while (pos[0] > row_) {
      ret.push_back({row_, col[i]});
      row_ ++;
    }
  }
  else if (pos[0] < row[i]) {
    row_ = row[i]-1;
    while (pos[0] < row_) {
      ret.push_back({row_, col[i]});
      row_ --;
    }
  }
  else if (pos[1] > col[i]) {
    col_ = col[i]+1;
    while (pos[1] > col_) {
      ret.push_back({row[i], col_});
      col_ ++;
    }
  }
  else if (pos[1] < col[i]) {
    col_ = col[i]-1;
    while (pos[1] < col_) {
      ret.push_back({row[i], col_});
      col_ --;
    }
  }
  return ret;
}

std::vector<int> Queen_Piece::get_avoid_move(int i) {
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
  else if (pos[0] > row[i])
    ret = {pos[0]+1, pos[1]};
  else if (pos[0] < row[i])
    ret = {pos[0]-1, pos[1]};
  else if (pos[1] > col[i])
    ret = {pos[0], pos[1]+1};
  else if (pos[1] < col[i])
    ret = {pos[0], pos[1]-1};
  return ret;
}

void Queen_Piece::update_movelist() {
  for (int i=0;i<num_queens;i++) {
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
    row_ = row[i]-1;
    col_ = col[i];
    while (row_ >= 0) {
      if (blocks[row_][col_]) {
        protecting_movelist[i].push_back({row_, col_});
        break;
      }
      movelist[i].push_back({row_, col_});
      if (White::blocks[row_][col_])
        break;
      row_ --;
    }
    row_ = row[i]+1;
    col_ = col[i];
    while (row_ < 8) {
      if (blocks[row_][col_]) {
        protecting_movelist[i].push_back({row_, col_});
        break;
      }
      movelist[i].push_back({row_, col_});
      if (White::blocks[row_][col_])
        break;
      row_ ++;
    }
    row_ = row[i];
    col_ = col[i]+1;
    while (col_ < 8) {
      if (blocks[row_][col_]) {
        protecting_movelist[i].push_back({row_, col_});
        break;
      }
      movelist[i].push_back({row_, col_});
      if (White::blocks[row_][col_])
        break;
      col_ ++;
    }
    row_ = row[i];
    col_ = col[i]-1;
    while (col_ >= 0) {
      if (blocks[row_][col_]) {
        protecting_movelist[i].push_back({row_, col_});
        break;
      }
      movelist[i].push_back({row_, col_});
      if (White::blocks[row_][col_])
        break;
      col_ --;
    }
  }
}

void Queen_Piece::move(int i, int row_, int col_) {
  blocks[row[i]][col[i]] = 0;
  blocks[row_][col_] = 1;
  row[i] = row_;
  col[i] = col_;
  x[i] = col[i]*UNIT;
  y[i] = row[i]*UNIT;
}

void Queen_Piece::show() {
  for (int i=0;i<num_queens;i++) {
    if (!alive[i])
      continue;
    if (!texture.loadFromFile("assets/sprites/blackQueen.png"))
      return;
    sprite.setTexture(texture);
    sprite.setScale(Board.pieces_scale, Board.pieces_scale);
    sprite.setPosition(x[i] + Board.pieces_paddingx, y[i] + Board.pieces_paddingy);
    window.draw(sprite);
  }
}

} // namespace Black
