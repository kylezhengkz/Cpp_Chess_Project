#include "boundary.h"
bool Boundary::inBounds(int x, int y) {
    return x >= 0 && x <= 7 && y >= 0 && y <= 7;
}

int* Boundary::stringSquareTo2DIndex(string s) { // convert square name to 2D x and y index
    int* index = new int[2];
    index[0] = s[0] - 'A';
    index[1] = s[1] - '1';
    if (!inBounds(index[0], index[1])) {
        throw InvalidSquareException(s);
    }
    return index;
}
