#ifndef MOVEIMPLEMENTER_H
#define MOVEIMPLEMENTER_H
#include <iostream>
#include "board.h"
#include "pawn.h"
#include "rook.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"
#include "constants.h"
#include "safetycomputor.h"
#include "checkexception.h"
namespace MoveImplementer {
    void implementMove(Board& board, bool user, istream& in, Piece* piece, Move& move);
};
#endif
