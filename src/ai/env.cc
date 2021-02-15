#include "../common/config.h"
#include "../common/util.h"

#include "../core/black/bishop.h"
#include "../core/black/knight.h"
#include "../core/black/pawn.h"
#include "../core/black/rook.h"
#include "../core/black/queen.h"
#include "../core/black/king.h"

#include "../core/white/bishop.h"
#include "../core/white/knight.h"
#include "../core/white/pawn.h"
#include "../core/white/rook.h"
#include "../core/white/queen.h"
#include "../core/white/king.h"

#include "../core/white_.h"
#include "../core/black_.h"

// Initialize the board with a custom environment for testing the AI.
// TODO: blocks needs to be set as well (i think?)
void init(const std::string& env) {
  if (env == "") return;
  else if (env == "onlypawns0") {
    Black::kill(true, "Q0", 0, 3);
    Black::kill(true, "K", 0, 4);
    for (int i=0;i<2;i++) {
      Black::kill(true, "B"+str(i), Black::bishop.row[i], Black::bishop.col[i]);
      Black::kill(true, "R"+str(i), Black::rook.row[i], Black::rook.col[i]);
      Black::kill(true, "N"+str(i), Black::knight.row[i], Black::knight.col[i]);
    }
    White::kill(true, "Q0", 7, 3);
    White::kill(true, "K", 7, 4);
    for (int i=0;i<2;i++) {
      White::kill(true, "B"+str(i), White::bishop.row[i], White::bishop.col[i]);
      White::kill(true, "R"+str(i), White::rook.row[i], White::rook.col[i]);
      White::kill(true, "N"+str(i), White::knight.row[i], White::knight.col[i]);
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
    Black::kill(true, "P3", Black::pawn.row[3], Black::pawn.col[3]);
    for (int i=0;i<3;i++)
      White::kill(true, "P" + str(i), White::pawn.row[i], White::pawn.col[i]);
    for (int i=4;i<8;i++)
      White::kill(true, "P" + str(i), White::pawn.row[i], White::pawn.col[i]);
    for (int i=0;i<2;i++)
      Black::kill(true, "P" + str(i), Black::pawn.row[i], Black::pawn.col[i]);
    for (int i=5;i<8;i++)
      Black::kill(true, "P" + str(i), Black::pawn.row[i], Black::pawn.col[i]);
    White::pawn.move(3, 4, 3);
  }
  else if (env == "KQP") {
    for (int i=0;i<2;i++) {
      Black::kill(true, "B" + str(i), Black::bishop.row[i], Black::bishop.col[i]);
      Black::kill(true, "R" + str(i), Black::rook.row[i], Black::rook.col[i]);
      Black::kill(true, "N" + str(i), Black::knight.row[i], Black::knight.col[i]);
      White::kill(true, "B" + str(i), White::bishop.row[i], White::bishop.col[i]);
      White::kill(true, "R" + str(i), White::rook.row[i], White::rook.col[i]);
      White::kill(true, "N" + str(i), White::knight.row[i], White::knight.col[i]);
    }
  }
  else if (env == "KRP") {
    for (int i=0;i<Black::num_queens;i++)
      Black::kill(true, "Q" + str(i), Black::queen.row[i], Black::queen.col[i]);
    for (int i=0;i<White::num_queens;i++)
      White::kill(true, "Q" + str(i), White::queen.row[i], White::queen.col[i]);
    for (int i=0;i<2;i++) {
      Black::kill(true, "B" + str(i), Black::bishop.row[i], Black::bishop.col[i]);
      Black::kill(true, "N" + str(i), Black::knight.row[i], Black::knight.col[i]);
      White::kill(true, "B" + str(i), White::bishop.row[i], White::bishop.col[i]);
      White::kill(true, "N" + str(i), White::knight.row[i], White::knight.col[i]);
    }
  }
  else if (env == "KBPQ") {
    for (int i=0;i<2;i++) {
      Black::kill(true, "N" + str(i), Black::knight.row[i], Black::knight.col[i]);
      White::kill(true, "N" + str(i), White::knight.row[i], White::knight.col[i]);
    }
    for (int i=0;i<8;i++) {
      Black::kill(true, "P" + str(i), Black::pawn.row[i], Black::pawn.col[i]);
      White::kill(true, "P" + str(i), White::pawn.row[i], White::pawn.col[i]);
    }
  }
  else if (env == "KNP") {
    for (int i=0;i<Black::num_queens;i++)
      Black::kill(true, "Q" + str(i), Black::queen.row[i], Black::queen.col[i]);
    for (int i=0;i<White::num_queens;i++)
      White::kill(true, "Q" + str(i), White::queen.row[i], White::queen.col[i]);
    for (int i=0;i<2;i++) {
      Black::kill(true, "B" + str(i), Black::bishop.row[i], Black::bishop.col[i]);
      White::kill(true, "B" + str(i), White::bishop.row[i], White::bishop.col[i]);
      Black::kill(true, "R" + str(i), Black::rook.row[i], Black::rook.col[i]);
      White::kill(true, "R" + str(i), White::rook.row[i], White::rook.col[i]);
    }
  }
  else if (env == "KN") {
    for (int i=0;i<Black::num_queens;i++)
      Black::kill(true, "Q" + str(i), Black::queen.row[i], Black::queen.col[i]);
    for (int i=0;i<White::num_queens;i++)
      White::kill(true, "Q" + str(i), White::queen.row[i], White::queen.col[i]);
    for (int i=0;i<2;i++) {
      Black::kill(true, "B" + str(i), Black::bishop.row[i], Black::bishop.col[i]);
      White::kill(true, "B" + str(i), White::bishop.row[i], White::bishop.col[i]);
      Black::kill(true, "R" + str(i), Black::rook.row[i], Black::rook.col[i]);
      White::kill(true, "R" + str(i), White::rook.row[i], White::rook.col[i]);
    }
    for (int i=0;i<8;i++) {
      Black::kill(true, "P" + str(i), Black::pawn.row[i], Black::pawn.col[i]);
      White::kill(true, "P" + str(i), White::pawn.row[i], White::pawn.col[i]);
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
    Black::kill(true, "B1", Black::bishop.row[1], Black::bishop.col[1]);
    Black::kill(true, "N1", Black::knight.row[1], Black::knight.col[1]);
  }
  else if (env == "CK1") {
    Black::kill(true, "B1", Black::bishop.row[1], Black::bishop.col[1]);
    Black::kill(true, "N1", Black::knight.row[1], Black::knight.col[1]);
    Black::kill(true, "B0", Black::bishop.row[0], Black::bishop.col[0]);
    Black::kill(true, "N0", Black::knight.row[0], Black::knight.col[0]);
    Black::kill(true, "R0", Black::rook.row[0], Black::rook.col[0]);
    Black::kill(true, "Q0", Black::queen.row[0], Black::queen.col[0]);
    for (int i=0;i<8;i++) {
      Black::kill(true, "P" + str(i), Black::pawn.row[i], Black::pawn.col[i]);
    }
  }
  else if (env == "CQ") {
    Black::kill(true, "B0", Black::bishop.row[0], Black::bishop.col[0]);
    Black::kill(true, "N0", Black::knight.row[0], Black::knight.col[0]);
    Black::kill(true, "Q0", Black::queen.row[0], Black::queen.col[0]);
  }
  else if (env == "KR") {
    for (int i=0;i<Black::num_queens;i++)
      Black::kill(true, "Q" + str(i), Black::queen.row[i], Black::queen.col[i]);
    for (int i=0;i<White::num_queens;i++)
      White::kill(true, "Q" + str(i), White::queen.row[i], White::queen.col[i]);
    for (int i=0;i<2;i++) {
      Black::kill(true, "B" + str(i), Black::bishop.row[i], Black::bishop.col[i]);
      White::kill(true, "B" + str(i), White::bishop.row[i], White::bishop.col[i]);
      Black::kill(true, "N" + str(i), Black::knight.row[i], Black::knight.col[i]);
      White::kill(true, "N" + str(i), White::knight.row[i], White::knight.col[i]);
    }
    for (int i=0;i<8;i++) {
      Black::kill(true, "P" + str(i), Black::pawn.row[i], Black::pawn.col[i]);
      White::kill(true, "P" + str(i), White::pawn.row[i], White::pawn.col[i]);
    }
    for (int i=0;i<8;i++) {
      White::blocks.push_back(std::vector<int>());
      Black::blocks.push_back(std::vector<int>());
      for (int k=0;k<8;k++) {
        White::blocks[i].push_back(0);
        Black::blocks[i].push_back(0);
      }
    }
    White::blocks[7][0] = 1;
    White::blocks[7][4] = 1;
    White::blocks[7][7] = 1;
    Black::blocks[0][0] = 1;
    Black::blocks[0][4] = 1;
    Black::blocks[0][7] = 1;
  }
}
