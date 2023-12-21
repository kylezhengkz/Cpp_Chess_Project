#ifndef BISHOP_H
#define BISHOP_H
#include "piece.h"
class Bishop: public Piece {
    double value;
  public:
    Bishop(int x, int y, int colour);
    ~Bishop() override;
    Bishop(Bishop& other);
    Bishop(Bishop&& other);
    Bishop& operator=(Bishop& other);
    Bishop& operator=(Bishop&& other);
    void generateMoves(Piece* (*board)[8][8]) override;
};
#endif
