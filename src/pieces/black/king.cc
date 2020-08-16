#include "../../../include/common.h"

namespace Black {

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
  for (int i=0;i<White::num_queens;i++) {
    for (int k=0;k<White::Queen.movelist[i].size();k++) {
      for (int j=0;j<movelist.size();j++) {
        if (movelist[j] == White::Queen.movelist[i][k]) {
          movelist[j].clear();
        }
      }
    }
    for (int k=0;k<White::Queen.protecting_movelist[i].size();k++) {
      for (int j=0;j<movelist.size();j++) {
        if (movelist[j] == White::Queen.protecting_movelist[i][k]) {
          movelist[j].clear();
        }
      }
    }
  }
  for (int i=0;i<8;i++) {
    for (int k=0;k<White::Pawn.hit_movelist[i].size();k++) {
      for (int j=0;j<movelist.size();j++) {
        if (movelist[j] == White::Pawn.hit_movelist[i][k]) {
          movelist[j].clear();
        }
      }
    }
  }
  for (int i=0;i<2;i++) {
    for (int k=0;k<White::Bishop.movelist[i].size();k++) {
      for (int j=0;j<movelist.size();j++) {
        if (movelist[j] == White::Bishop.movelist[i][k]) {
          movelist[j].clear();
        }
      }
    }
    for (int k=0;k<White::Bishop.protecting_movelist[i].size();k++) {
      for (int j=0;j<movelist.size();j++) {
        if (movelist[j] == White::Bishop.protecting_movelist[i][k]) {
          movelist[j].clear();
        }
      }
    }
    for (int k=0;k<White::Knight.movelist[i].size();k++) {
      for (int j=0;j<movelist.size();j++) {
        if (movelist[j] == White::Knight.movelist[i][k]) {
          movelist[j].clear();
        }
      }
    }
    for (int k=0;k<White::Knight.protecting_movelist[i].size();k++) {
      for (int j=0;j<movelist.size();j++) {
        if (movelist[j] == White::Knight.protecting_movelist[i][k]) {
          movelist[j].clear();
        }
      }
    }
    for (int k=0;k<White::Rook.movelist[i].size();k++) {
      for (int j=0;j<movelist.size();j++) {
        if (movelist[j] == White::Rook.movelist[i][k]) {
          movelist[j].clear();
        }
      }
    }
    for (int k=0;k<White::Rook.protecting_movelist[i].size();k++) {
      for (int j=0;j<movelist.size();j++) {
        if (movelist[j] == White::Rook.protecting_movelist[i][k]) {
          movelist[j].clear();
        }
      }
    }
  }
}

void King_Piece::filter_king_pos() {
  std::vector<std::vector<int>> opposite_pos = {
  {White::King.row-1, White::King.col-1}, {White::King.row-1, White::King.col},
  {White::King.row-1, White::King.col+1}, {White::King.row, White::King.col-1},
  {White::King.row, White::King.col}, {White::King.row, White::King.col+1},
  {White::King.row+1, White::King.col-1}, {White::King.row+1, White::King.col},
  {White::King.row+1, White::King.col+1}
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
  if (!texture.loadFromFile("assets/sprites/blackKing.png"))
    return;
  sf::Sprite sprite;
  sprite.setTexture(texture);
  sprite.setScale(Board.pieces_scale, Board.pieces_scale);
  sprite.setPosition(x + Board.pieces_paddingx, y + Board.pieces_paddingy);
  window.draw(sprite);
}

} // namespace Black
