#include "movelist.h"
void MoveList::addToFront(int toX, int toY, double value, bool isCapture) {
    list = new Move(toX, toY, value, isCapture, list);
}

Move* MoveList::getFront() {
    return list;
}

MoveList::~MoveList() {
    delete list;
}

MoveList::Iterator MoveList::begin() {
    return Iterator(list);
}
    
MoveList::Iterator MoveList::end() {
    return Iterator(nullptr);
}
