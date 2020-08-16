#include "../../../include/common.h"

namespace White {

void King_Piece::update_movelist() {
  if (!alive)
    return;
  movelist.clear();
  std::vector<std::vector<int>> pos = {
  {row-1, col-1}, {row-1, col}, {row-1, col+1},
  {row, col-1}, {row, col}, {row, col+1},
  {row+1, col-1}, {row+1, col}, {row+1, col+1},
  };
  for (int k=0;k<pos.size();k++) {
    if (pos[k][0] >= 0 && pos[k][0] < 8 && pos[k][1] >= 0 && pos[k][1] < 8) {
      if (!blocks[pos[k][0]][pos[k][1]])
        movelist.push_back({pos[k][0], pos[k][1]});
    }
  }
  filter_king_pos();
  filter_check_pos();
}

void King_Piece::filter_check_pos() {
  std::vector<std::vector<int>> pos;
  for (int i=0;i<Black::num_queens;i++) {
    for (int k=0;k<Black::Queen.movelist[i].size();k++) {
      for (int j=0;j<movelist.size();j++) {
        if (movelist[j] == Black::Queen.movelist[i][k]) {
          movelist[j].clear();
        }
      }
    }
    for (int k=0;k<Black::Queen.protecting_movelist[i].size();k++) {
      for (int j=0;j<movelist.size();j++) {
        if (movelist[j] == Black::Queen.protecting_movelist[i][k]) {
          movelist[j].clear();
        }
      }
    }
  }
  for (int i=0;i<8;i++) {
    for (int k=0;k<Black::Pawn.hit_movelist[i].size();k++) {
      for (int j=0;j<movelist.size();j++) {
        if (movelist[j] == Black::Pawn.hit_movelist[i][k]) {
          movelist[j].clear();
        }
      }
    }
  }
  for (int i=0;i<2;i++) {
    for (int k=0;k<Black::Bishop.movelist[i].size();k++) {
      for (int j=0;j<movelist.size();j++) {
        if (movelist[j] == Black::Bishop.movelist[i][k]) {
          movelist[j].clear();
        }
      }
    }
    for (int k=0;k<Black::Bishop.protecting_movelist[i].size();k++) {
      for (int j=0;j<movelist.size();j++) {
        if (movelist[j] == Black::Bishop.protecting_movelist[i][k]) {
          movelist[j].clear();
        }
      }
    }
    for (int k=0;k<Black::Knight.movelist[i].size();k++) {
      for (int j=0;j<movelist.size();j++) {
        if (movelist[j] == Black::Knight.movelist[i][k]) {
          movelist[j].clear();
        }
      }
    }
    for (int k=0;k<Black::Knight.protecting_movelist[i].size();k++) {
      for (int j=0;j<movelist.size();j++) {
        if (movelist[j] == Black::Knight.protecting_movelist[i][k]) {
          movelist[j].clear();
        }
      }
    }
    for (int k=0;k<Black::Rook.movelist[i].size();k++) {
      for (int j=0;j<movelist.size();j++) {
        if (movelist[j] == Black::Rook.movelist[i][k]) {
          movelist[j].clear();
        }
      }
    }
    for (int k=0;k<Black::Rook.protecting_movelist[i].size();k++) {
      for (int j=0;j<movelist.size();j++) {
        if (movelist[j] == Black::Rook.protecting_movelist[i][k]) {
          movelist[j].clear();
        }
      }
    }
  }
}

void King_Piece::filter_king_pos() {
  std::vector<std::vector<int>> opposite_pos = {
  {Black::King.row-1, Black::King.col-1}, {Black::King.row-1, Black::King.col},
  {Black::King.row-1, Black::King.col+1}, {Black::King.row, Black::King.col-1},
  {Black::King.row, Black::King.col}, {Black::King.row, Black::King.col+1},
  {Black::King.row+1, Black::King.col-1}, {Black::King.row+1, Black::King.col},
  {Black::King.row+1, Black::King.col+1}
  };
  for (int i=0;i<opposite_pos.size();i++) {
    for (int k=0;k<movelist.size();k++) {
      if (movelist[k] == opposite_pos[i])
        movelist[k].clear();
    }
  }
}

void King_Piece::move(int row_, int col_) {
  blocks[row][col] = 0;
  blocks[row_][col_] = 1;
  row = row_;
  col = col_;
  x = col*UNIT;
  y = row*UNIT;
}

void King_Piece::show() {
  if (!alive)
    return;
  sf::Texture texture;
  if (!texture.loadFromFile("assets/sprites/whiteKing.png"))
    return;
  sf::Sprite sprite;
  sprite.setTexture(texture);
  sprite.setScale(Board.pieces_scale, Board.pieces_scale);
  sprite.setPosition(x + Board.pieces_paddingx, y + Board.pieces_paddingy);
  window.draw(sprite);
}

} // namespace White
