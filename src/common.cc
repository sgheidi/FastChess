#include "common.h"

bool testing = true;
struct undo_stack undo = {
  {},
  {""},
  {""}
};

// This function removes any elements in v1 that are in v2
std::vector<std::vector<int>>
filter2(std::vector<std::vector<int>> v1, std::vector<std::vector<int>> v2) {
  for (int i=0;i<v1.size();i++) {
    if (in(v2, v1[i])) {
      v1.erase(v1.begin() + i);
      i--;
    }
  }
  return v1;
}

// This function removes any elements in v1 that are not in v2
std::vector<std::vector<int>>
filter(std::vector<std::vector<int>> v1, std::vector<std::vector<int>> v2) {
  for (int i=0;i<v1.size();i++) {
    if (!in(v2, v1[i])) {
      v1.erase(v1.begin() + i);
      i--;
    }
  }
  return v1;
}

void print_v3(std::vector<std::vector<std::vector<int>>> v) {
  printf("vec3d...\n");
  for (int i=0;i<v.size();i++) {
    for (int k=0;k<v[i].size();k++) {
      for (int j=0;j<v[i][k].size();j++) {
        printf("%d", v[i][k][j]);
      }
      printf(" ");
    }
    printf("\n");
  }
  printf("\n");
}

void print_v1(std::vector<int> v) {
  printf("vec1d...\n");
  for (int i=0;i<v.size();i++) {
    printf("%d", v[i]);
  }
  printf("\n");
}

void print_v2(std::vector<std::vector<int>> v) {
  printf("vec2d...\n");
  for (int i=0;i<v.size();i++) {
    for (int k=0;k<v[i].size();k++) {
      printf("%d", v[i][k]);
    }
    printf(" ");
  }
  printf("\n");
}

// return true if 1d vector in 2d vector
bool in(std::vector<std::vector<int>> v, std::vector<int> item) {
  if (std::find(v.begin(), v.end(), item) != v.end())
    return true;
  return false;
}

Game_Board Board;
Click_Queue Queue;
Game_Sound Sound;
Game_Text Text;

namespace Black {
Bishop_Piece Bishop;
Knight_Piece Knight;
Pawn_Piece Pawn;
Rook_Piece Rook;
King_Piece King;
Queen_Piece Queen;
}

namespace White {
Bishop_Piece Bishop;
Knight_Piece Knight;
Pawn_Piece Pawn;
Rook_Piece Rook;
King_Piece King;
Queen_Piece Queen;
}

sf::RenderWindow window(sf::VideoMode(X_RES, Y_RES), "FastChess");
