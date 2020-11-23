#include "../common.h"

// Initialize the board with a custom environment for testing the AI.
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
  else if (env == "KRP") {
    for (int i=0;i<Black::num_queens;i++)
      Black::kill(true, "Q" + str(i), Black::Queen.row[i], Black::Queen.col[i]);
    for (int i=0;i<White::num_queens;i++)
      White::kill(true, "Q" + str(i), White::Queen.row[i], White::Queen.col[i]);
    for (int i=0;i<2;i++) {
      Black::kill(true, "B" + str(i), Black::Bishop.row[i], Black::Bishop.col[i]);
      Black::kill(true, "N" + str(i), Black::Knight.row[i], Black::Knight.col[i]);
      White::kill(true, "B" + str(i), White::Bishop.row[i], White::Bishop.col[i]);
      White::kill(true, "N" + str(i), White::Knight.row[i], White::Knight.col[i]);
    }
  }
  else if (env == "KBPQ") {
    for (int i=0;i<2;i++) {
      Black::kill(true, "N" + str(i), Black::Knight.row[i], Black::Knight.col[i]);
      White::kill(true, "N" + str(i), White::Knight.row[i], White::Knight.col[i]);
    }
    for (int i=0;i<8;i++) {
      Black::kill(true, "P" + str(i), Black::Pawn.row[i], Black::Pawn.col[i]);
      White::kill(true, "P" + str(i), White::Pawn.row[i], White::Pawn.col[i]);
    }
  }
  else if (env == "KNP") {
    for (int i=0;i<Black::num_queens;i++)
      Black::kill(true, "Q" + str(i), Black::Queen.row[i], Black::Queen.col[i]);
    for (int i=0;i<White::num_queens;i++)
      White::kill(true, "Q" + str(i), White::Queen.row[i], White::Queen.col[i]);
    for (int i=0;i<2;i++) {
      Black::kill(true, "B" + str(i), Black::Bishop.row[i], Black::Bishop.col[i]);
      White::kill(true, "B" + str(i), White::Bishop.row[i], White::Bishop.col[i]);
      Black::kill(true, "R" + str(i), Black::Rook.row[i], Black::Rook.col[i]);
      White::kill(true, "R" + str(i), White::Rook.row[i], White::Rook.col[i]);
    }
  }
  else if (env == "KN") {
    for (int i=0;i<Black::num_queens;i++)
      Black::kill(true, "Q" + str(i), Black::Queen.row[i], Black::Queen.col[i]);
    for (int i=0;i<White::num_queens;i++)
      White::kill(true, "Q" + str(i), White::Queen.row[i], White::Queen.col[i]);
    for (int i=0;i<2;i++) {
      Black::kill(true, "B" + str(i), Black::Bishop.row[i], Black::Bishop.col[i]);
      White::kill(true, "B" + str(i), White::Bishop.row[i], White::Bishop.col[i]);
      Black::kill(true, "R" + str(i), Black::Rook.row[i], Black::Rook.col[i]);
      White::kill(true, "R" + str(i), White::Rook.row[i], White::Rook.col[i]);
    }
    for (int i=0;i<8;i++) {
      Black::kill(true, "P" + str(i), Black::Pawn.row[i], Black::Pawn.col[i]);
      White::kill(true, "P" + str(i), White::Pawn.row[i], White::Pawn.col[i]);
    }
    for (int i=0;i<8;i++) {
      White::blocks.push_back(std::vector<int>());
      Black::blocks.push_back(std::vector<int>());
      for (int k=0;k<8;k++) {
        White::blocks[i].push_back(0);
        Black::blocks[i].push_back(0);
      }
    }
    White::blocks[7][1] = 1;
    White::blocks[7][6] = 1;
    White::blocks[7][4] = 1;
    Black::blocks[0][1] = 1;
    Black::blocks[0][6] = 1;
    Black::blocks[0][4] = 1;
  }
  else if (env == "CK0") {
    Black::kill(true, "B1", Black::Bishop.row[1], Black::Bishop.col[1]);
    Black::kill(true, "N1", Black::Knight.row[1], Black::Knight.col[1]);
  }
  else if (env == "CK1") {
    Black::kill(true, "B1", Black::Bishop.row[1], Black::Bishop.col[1]);
    Black::kill(true, "N1", Black::Knight.row[1], Black::Knight.col[1]);
    Black::kill(true, "B0", Black::Bishop.row[0], Black::Bishop.col[0]);
    Black::kill(true, "N0", Black::Knight.row[0], Black::Knight.col[0]);
    Black::kill(true, "R0", Black::Rook.row[0], Black::Rook.col[0]);
    Black::kill(true, "Q0", Black::Queen.row[0], Black::Queen.col[0]);
    for (int i=0;i<8;i++) {
      Black::kill(true, "P" + str(i), Black::Pawn.row[i], Black::Pawn.col[i]);
    }
  }
  else if (env == "CQ") {
    Black::kill(true, "B0", Black::Bishop.row[0], Black::Bishop.col[0]);
    Black::kill(true, "N0", Black::Knight.row[0], Black::Knight.col[0]);
    Black::kill(true, "Q0", Black::Queen.row[0], Black::Queen.col[0]);
  }
}
