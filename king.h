#ifndef KING_H
#define KING_H
#include "piece.h"
#include "rook.h"
#include "safetycomputor.h"
class Rook;
class King: public Piece {
    bool castleEligibility = true;
    Rook* leftRook = nullptr;
    Rook* rightRook = nullptr;
    void checkCastling(Piece* (*board)[8][8]);
  public:
    King(int x, int y, int colour);
    ~King() override;
    void moveKing();
    Rook* getLeftRook();
    Rook* getRightRook();
    bool canCastle();
    void attachLeftRook(Rook* attachedLeftRook);
    void attachRightRook(Rook* attachedRightRook);
    King(King& other);
    King(King&& other);
    King& operator=(King& other);
    King& operator=(King&& other);
    void generateMoves(Piece* (*board)[8][8]) override;
};
#endif
