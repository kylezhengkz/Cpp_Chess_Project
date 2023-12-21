#ifndef PIECE_H
#define PIECE_H
#include <vector>
#include "movelist.h"
#include "boundary.h"
#include "constants.h"
#include <cmath>
#include <utility>
using namespace std;
class Piece {
    int x;
    int y;
    int colour;
    double value;
    MoveList* moveList;
  public:
    Piece();
    Piece(int x, int y, int colour, double value);
    void reNullify();
    virtual ~Piece();
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    int getColour();
    double getValue();
    MoveList* getList();
    Piece(Piece& other);
    Piece(Piece&& other);
    Piece& operator=(Piece& other);
    Piece& operator=(Piece&& other);
    virtual void generateMoves(Piece* (*board)[8][8]) = 0;
};
#endif
