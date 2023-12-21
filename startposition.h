#ifndef STARTPOSITION_H
#define STARTINGPOSITION_H
#include "board.h"
#include "pawn.h"
#include "rook.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"
#include "constants.h"
#include "invalidsquareexception.h"
#include "invalidinputexception.h"
#include "nokingexception.h"
#include "textdisplay.h"
#include <iostream>
#include <sstream>
namespace StartPosition {
  void defaultStartingPosition(Board* currentPosition);
  void setupPawns(Board* currentPosition);
  void setupBlackPieces(Board* currentPosition);
  void setupWhitePieces(Board* currentPosition);
  void setup(istream& in, Board* currentPosition, ostream& out, TextDisplay* textDisplay, int& turn);
};
#endif
