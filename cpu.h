#ifndef CPU_H
#define CPU_H
#include "computer.h"
#include "board.h"
#include "moveimplementer.h"
#include <sstream>
#include <random>
#include <map>
#include "checkmateexception.h"
#include "stalemateexception.h"
class CPU: public Computer {
    Board* board;
    int* colour;
    map<Board*, double>* newPositions = new map<Board*, double>(); // maps new position with a value
 public:
    CPU(Board* board, int* colour);
    void selectBestMove() override;
    map<Board*, double>* evalMoves() override;
    Board* getBoard() override;
    int getColour() override;

    void setBoard(Board* board) override;
};
#endif
