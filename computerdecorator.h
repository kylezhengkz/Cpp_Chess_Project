#ifndef COMPUTERDECORATOR_H
#define COMPUTERDECORATOR_H
#include "computer.h"
#include "board.h"
#include "moveimplementer.h"
using namespace std;
class ComputerDecorator: public Computer {
  protected:
    Computer* next;
  public:
	ComputerDecorator(Computer* c);
  ~ComputerDecorator();
};
#endif
