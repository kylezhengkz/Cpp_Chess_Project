#ifndef CHECKMATEFINDER_H
#define CHECKMATEFINDER_H
#include "computerdecorator.h"
#include <map>
#include <sstream>
#include "safetycomputor.h"
class CheckmateFinder: public ComputerDecorator {
  public:
    CheckmateFinder(Computer* next);
    void selectBestMove() override;
	map<Board*, double>* evalMoves() override;
    Board* getBoard();
    int getColour();
    void setBoard(Board* newPosition);
};
#endif
