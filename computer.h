#ifndef COMPUTER_H
#define COMPUTER_H
#include <map>
using namespace std;
class Board;
class Computer {
  public:
    virtual void selectBestMove() = 0;
    virtual map<Board*, double>* evalMoves() = 0;
    virtual ~Computer();
    virtual Board* getBoard() = 0;
    virtual int getColour() = 0;
    virtual void setBoard(Board* board) = 0;
};

#endif
