#ifndef ROOK_H
#define ROOK_H
#include "piece.h"
class Rook: public Piece {
    bool castleEligibility = false;
  public:
    Rook(int x, int y, int colour);
    ~Rook() override;
    bool eligibleToCastle();
    void enableCastle();
    void moveRook();
    Rook(Rook& other);
    Rook(Rook&& other);
    void generateMoves(Piece* (*board)[8][8]) override;
};
#endif
