#ifndef MOVELIST_H
#define MOVELIST_H
#include "move.h"
class MoveList {
    Move* list = nullptr;
  public:
    void addToFront(int toX, int toY, double value, bool isCapture);
    Move* getFront();
    ~MoveList();

    class Iterator {
	      Move* p;
      public:
	      explicit Iterator(Move* p): p{p} {}
	      Move*& operator*() { return p; }
			
	      Iterator& operator++() {
		        p = p->getNext();
		        return *this;
	      }

	      bool operator!=(const Iterator& other) const {
		        return p != other.p;
	      }
    };

    Iterator begin();
    Iterator end();
};
#endif
