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
    black::kill(true, "Q0", 0, 3);
    black::kill(true, "K", 0, 4);
    for (int i=0;i<2;i++) {
      black::kill(true, "B"+str(i), black::bishop.row[i], black::bishop.col[i]);
      black::kill(true, "R"+str(i), black::rook.row[i], black::rook.col[i]);
      black::kill(true, "N"+str(i), black::knight.row[i], black::knight.col[i]);
    }
    white::kill(true, "Q0", 7, 3);
    white::kill(true, "K", 7, 4);
    for (int i=0;i<2;i++) {
      white::kill(true, "B"+str(i), white::bishop.row[i], white::bishop.col[i]);
      white::kill(true, "R"+str(i), white::rook.row[i], white::rook.col[i]);
      white::kill(true, "N"+str(i), white::knight.row[i], white::knight.col[i]);
    }
    for (int i=0;i<8;i++) {
      black::blocks.push_back(std::vector<int>());
      for (int k=0;k<8;k++) {
        if (i == 1)
          black::blocks[i].push_back(1);
        else
          black::blocks[i].push_back(0);
      }
    }
    for (int i=0;i<8;i++) {
      white::blocks.push_back(std::vector<int>());
      for (int k=0;k<8;k++) {
        if (i == 6)
          white::blocks[i].push_back(1);
        else
          white::blocks[i].push_back(0);
      }
    }
  }
  else if (env == "enpassant0") {
    init("onlypawns0");
    black::kill(true, "P3", black::pawn.row[3], black::pawn.col[3]);
    for (int i=0;i<3;i++)
      white::kill(true, "P" + str(i), white::pawn.row[i], white::pawn.col[i]);
    for (int i=4;i<8;i++)
      white::kill(true, "P" + str(i), white::pawn.row[i], white::pawn.col[i]);
    for (int i=0;i<2;i++)
      black::kill(true, "P" + str(i), black::pawn.row[i], black::pawn.col[i]);
    for (int i=5;i<8;i++)
      black::kill(true, "P" + str(i), black::pawn.row[i], black::pawn.col[i]);
    white::pawn.move(3, 4, 3);
  }
  else if (env == "KQP") {
    for (int i=0;i<2;i++) {
      black::kill(true, "B" + str(i), black::bishop.row[i], black::bishop.col[i]);
      black::kill(true, "R" + str(i), black::rook.row[i], black::rook.col[i]);
      black::kill(true, "N" + str(i), black::knight.row[i], black::knight.col[i]);
      white::kill(true, "B" + str(i), white::bishop.row[i], white::bishop.col[i]);
      white::kill(true, "R" + str(i), white::rook.row[i], white::rook.col[i]);
      white::kill(true, "N" + str(i), white::knight.row[i], white::knight.col[i]);
    }
  }
  else if (env == "KRP") {
    for (int i=0;i<black::num_queens;i++)
      black::kill(true, "Q" + str(i), black::queen.row[i], black::queen.col[i]);
    for (int i=0;i<white::num_queens;i++)
      white::kill(true, "Q" + str(i), white::queen.row[i], white::queen.col[i]);
    for (int i=0;i<2;i++) {
      black::kill(true, "B" + str(i), black::bishop.row[i], black::bishop.col[i]);
      black::kill(true, "N" + str(i), black::knight.row[i], black::knight.col[i]);
      white::kill(true, "B" + str(i), white::bishop.row[i], white::bishop.col[i]);
      white::kill(true, "N" + str(i), white::knight.row[i], white::knight.col[i]);
    }
  }
  else if (env == "KBPQ") {
    for (int i=0;i<2;i++) {
      black::kill(true, "N" + str(i), black::knight.row[i], black::knight.col[i]);
      white::kill(true, "N" + str(i), white::knight.row[i], white::knight.col[i]);
    }
    for (int i=0;i<8;i++) {
      black::kill(true, "P" + str(i), black::pawn.row[i], black::pawn.col[i]);
      white::kill(true, "P" + str(i), white::pawn.row[i], white::pawn.col[i]);
    }
  }
  else if (env == "KNP") {
    for (int i=0;i<black::num_queens;i++)
      black::kill(true, "Q" + str(i), black::queen.row[i], black::queen.col[i]);
    for (int i=0;i<white::num_queens;i++)
      white::kill(true, "Q" + str(i), white::queen.row[i], white::queen.col[i]);
    for (int i=0;i<2;i++) {
      black::kill(true, "B" + str(i), black::bishop.row[i], black::bishop.col[i]);
      white::kill(true, "B" + str(i), white::bishop.row[i], white::bishop.col[i]);
      black::kill(true, "R" + str(i), black::rook.row[i], black::rook.col[i]);
      white::kill(true, "R" + str(i), white::rook.row[i], white::rook.col[i]);
    }
  }
  else if (env == "KN") {
    for (int i=0;i<black::num_queens;i++)
      black::kill(true, "Q" + str(i), black::queen.row[i], black::queen.col[i]);
    for (int i=0;i<white::num_queens;i++)
      white::kill(true, "Q" + str(i), white::queen.row[i], white::queen.col[i]);
    for (int i=0;i<2;i++) {
      black::kill(true, "B" + str(i), black::bishop.row[i], black::bishop.col[i]);
      white::kill(true, "B" + str(i), white::bishop.row[i], white::bishop.col[i]);
      black::kill(true, "R" + str(i), black::rook.row[i], black::rook.col[i]);
      white::kill(true, "R" + str(i), white::rook.row[i], white::rook.col[i]);
    }
    for (int i=0;i<8;i++) {
      black::kill(true, "P" + str(i), black::pawn.row[i], black::pawn.col[i]);
      white::kill(true, "P" + str(i), white::pawn.row[i], white::pawn.col[i]);
    }
    for (int i=0;i<8;i++) {
      white::blocks.push_back(std::vector<int>());
      black::blocks.push_back(std::vector<int>());
      for (int k=0;k<8;k++) {
        white::blocks[i].push_back(0);
        black::blocks[i].push_back(0);
      }
    }
    white::blocks[7][1] = 1;
    white::blocks[7][6] = 1;
    white::blocks[7][4] = 1;
    black::blocks[0][1] = 1;
    black::blocks[0][6] = 1;
    black::blocks[0][4] = 1;
  }
  else if (env == "CK0") {
    black::kill(true, "B1", black::bishop.row[1], black::bishop.col[1]);
    black::kill(true, "N1", black::knight.row[1], black::knight.col[1]);
  }
  else if (env == "CK1") {
    black::kill(true, "B1", black::bishop.row[1], black::bishop.col[1]);
    black::kill(true, "N1", black::knight.row[1], black::knight.col[1]);
    black::kill(true, "B0", black::bishop.row[0], black::bishop.col[0]);
    black::kill(true, "N0", black::knight.row[0], black::knight.col[0]);
    black::kill(true, "R0", black::rook.row[0], black::rook.col[0]);
    black::kill(true, "Q0", black::queen.row[0], black::queen.col[0]);
    for (int i=0;i<8;i++) {
      black::kill(true, "P" + str(i), black::pawn.row[i], black::pawn.col[i]);
    }
  }
  else if (env == "CQ") {
    black::kill(true, "B0", black::bishop.row[0], black::bishop.col[0]);
    black::kill(true, "N0", black::knight.row[0], black::knight.col[0]);
    black::kill(true, "Q0", black::queen.row[0], black::queen.col[0]);
  }
  else if (env == "KR") {
    for (int i=0;i<black::num_queens;i++)
      black::kill(true, "Q" + str(i), black::queen.row[i], black::queen.col[i]);
    for (int i=0;i<white::num_queens;i++)
      white::kill(true, "Q" + str(i), white::queen.row[i], white::queen.col[i]);
    for (int i=0;i<2;i++) {
      black::kill(true, "B" + str(i), black::bishop.row[i], black::bishop.col[i]);
      white::kill(true, "B" + str(i), white::bishop.row[i], white::bishop.col[i]);
      black::kill(true, "N" + str(i), black::knight.row[i], black::knight.col[i]);
      white::kill(true, "N" + str(i), white::knight.row[i], white::knight.col[i]);
    }
    for (int i=0;i<8;i++) {
      black::kill(true, "P" + str(i), black::pawn.row[i], black::pawn.col[i]);
      white::kill(true, "P" + str(i), white::pawn.row[i], white::pawn.col[i]);
    }
    for (int i=0;i<8;i++) {
      white::blocks.push_back(std::vector<int>());
      black::blocks.push_back(std::vector<int>());
      for (int k=0;k<8;k++) {
        white::blocks[i].push_back(0);
        black::blocks[i].push_back(0);
      }
    }
    white::blocks[7][0] = 1;
    white::blocks[7][4] = 1;
    white::blocks[7][7] = 1;
    black::blocks[0][0] = 1;
    black::blocks[0][4] = 1;
    black::blocks[0][7] = 1;
  }
}
