#include "direction.h"
bool Direction::isDiagonal(int deltaX, int deltaY) {
    return abs(deltaX) == abs(deltaY);
}
bool Direction::isStraight(int deltaX, int deltaY) {
    return (abs(deltaX) == 1 && deltaY == 0) || (deltaX == 0 && abs(deltaY) == 1);
}
