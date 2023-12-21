#ifndef QUEEN_H
#define QUEEN_H
#include "piece.h"
class Queen: public Piece {
    double value = 9;
  public:
    Queen(int x, int y, int colour);
    ~Queen() override;
    Queen(Queen& other);
    Queen(Queen&& other);
    Queen& operator=(Queen& other);
    Queen& operator=(Queen&& other);
    void generateMoves(Piece* (*board)[8][8]) override;
};
#endif
