#include "../common.h"

std::map<std::string, std::vector<int>> get_all_white_moves():
  std::map<std::string, std::vector<int>> moves = {};
  if WhiteKing.alive and WhiteKing.movelist != []:
    moves["K"] = WhiteKing.movelist.copy()
    if White_.castle_criteria_king():
      moves["K"].append("CK")
    if White_.castle_criteria_queen():
      moves["K"].append("CQ")
  for i in range(White.num_queens):
    if WhiteQueen.alive[i] and WhiteQueen.movelist[i] != []:
      moves["Q" + str(i)] = WhiteQueen.movelist[i].copy()
  for i in range(8):
    if WhitePawn.alive[i] and WhitePawn.movelist[i] != []:
      moves["P" + str(i)] = WhitePawn.movelist[i].copy()
  for i in range(2):
    if WhiteBishop.alive[i] and WhiteBishop.movelist[i] != []:
      moves["B" + str(i)] = WhiteBishop.movelist[i].copy()
    if WhiteKnight.alive[i] and WhiteKnight.movelist[i] != []:
      moves["N" + str(i)] = WhiteKnight.movelist[i].copy()
    if WhiteRook.alive[i] and WhiteRook.movelist[i] != []:
      moves["R" + str(i)] = WhiteRook.movelist[i].copy()
  return self.shuffle(moves)
