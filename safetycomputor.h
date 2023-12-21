#ifndef SAFETYCOMPUTOR_H
#define SAFETYCOMPUTOR_H
#include "board.h"
#include "boundary.h"
#include "direction.h"
#include "pawn.h"
#include "rook.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"
using namespace std;
namespace SafetyComputor {
    bool isSquareSafe(Piece* (*board)[8][8], int x, int y, int oppositionColour);
};
#endif
