#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"
class Knight: public Piece {
    double value = 3;
  public:
    Knight(int x, int y, int colour);
    ~Knight() override;
    Knight(Knight& other);
    Knight(Knight&& other);
    Knight& operator=(Knight& other);
    Knight& operator=(Knight&& other);
    void generateMoves(Piece* (*board)[8][8]) override;
};
#endif
