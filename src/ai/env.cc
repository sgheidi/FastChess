#include "../common.h"

// Initialize the board with a custom environment for testing.
void init(std::string env) {
  if (env == "") return;
  else if (env == "onlypawns0") {
    Black::kill(true, "Q0", 0, 3);
    Black::kill(true, "K", 0, 4);
    for (int i=0;i<2;i++) {
      Black::kill(true, "B"+str(i), Black::Bishop.row[i], Black::Bishop.col[i]);
      Black::kill(true, "R"+str(i), Black::Rook.row[i], Black::Rook.col[i]);
      Black::kill(true, "N"+str(i), Black::Knight.row[i], Black::Knight.col[i]);
    }
    White::kill(true, "Q0", 7, 3);
    White::kill(true, "K", 7, 4);
    for (int i=0;i<2;i++) {
      White::kill(true, "B"+str(i), White::Bishop.row[i], White::Bishop.col[i]);
      White::kill(true, "R"+str(i), White::Rook.row[i], White::Rook.col[i]);
      White::kill(true, "N"+str(i), White::Knight.row[i], White::Knight.col[i]);
    }
    for (int i=0;i<8;i++) {
      Black::blocks.push_back(std::vector<int>());
      for (int k=0;k<8;k++) {
        if (i == 1)
          Black::blocks[i].push_back(1);
        else
          Black::blocks[i].push_back(0);
      }
    }
    for (int i=0;i<8;i++) {
      White::blocks.push_back(std::vector<int>());
      for (int k=0;k<8;k++) {
        if (i == 6)
          White::blocks[i].push_back(1);
        else
          White::blocks[i].push_back(0);
      }
    }
  }
  else if (env == "enpassant0") {
    init("onlypawns0");
    Black::kill(true, "P3", Black::Pawn.row[3], Black::Pawn.col[3]);
    for (int i=0;i<3;i++)
      White::kill(true, "P" + str(i), White::Pawn.row[i], White::Pawn.col[i]);
    for (int i=4;i<8;i++)
      White::kill(true, "P" + str(i), White::Pawn.row[i], White::Pawn.col[i]);
    for (int i=0;i<2;i++)
      Black::kill(true, "P" + str(i), Black::Pawn.row[i], Black::Pawn.col[i]);
    for (int i=5;i<8;i++)
      Black::kill(true, "P" + str(i), Black::Pawn.row[i], Black::Pawn.col[i]);
    White::Pawn.move(3, 4, 3);
  }
  else if (env == "KQP") {
    for (int i=0;i<2;i++) {
      Black::kill(true, "B" + str(i), Black::Bishop.row[i], Black::Bishop.col[i]);
      Black::kill(true, "R" + str(i), Black::Rook.row[i], Black::Rook.col[i]);
      Black::kill(true, "N" + str(i), Black::Knight.row[i], Black::Knight.col[i]);
      White::kill(true, "B" + str(i), White::Bishop.row[i], White::Bishop.col[i]);
      White::kill(true, "R" + str(i), White::Rook.row[i], White::Rook.col[i]);
      White::kill(true, "N" + str(i), White::Knight.row[i], White::Knight.col[i]);
    }
  }
}
