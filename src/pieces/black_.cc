#include "../../include/common.h"

void Black_Pieces::play() {

  turn = false;
}

void Black_Pieces::print_blocks() {
  for (int i=0;i<8;i++) {
    for (int k=0;k<8;k++)
      printf("%d", blocks[i][k]);
    printf("\n");
  }
}

void Black_Pieces::show() {
  BBishop.show();
  BKnight.show();
  BPawn.show();
  BRook.show();
  BKing.show();
  BQueen.show();
}
