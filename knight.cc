#include "knight.h"
Knight::Knight(int x, int y, int colour): Piece{x, y, colour, 3} {}

Knight::~Knight() {}

Knight::Knight(Knight& other): Piece{other} {}

Knight::Knight(Knight&& other): Piece{other} {}

Knight& Knight::operator=(Knight& other) {
    Piece::operator=(other);
    return *this;
}

Knight& Knight::operator=(Knight&& other) {
    Piece::operator=(other);
    return *this;
}

void Knight::generateMoves(Piece* (*board)[8][8]) {
    for (int i = 0; i < 8; i++) {
        int deltaX;
        int deltaY;
        if (i == 0) {
            deltaX = 1;
            deltaY = 2;
        } else if (i == 1) {
            deltaX = 1;
            deltaY = -2;
        } else if (i == 2) {
            deltaX = -1;
            deltaY = 2;
        } else if (i == 3) {
            deltaX = -1;
            deltaY = -2;
        } else if (i == 4) {
            deltaX = 2;
            deltaY = 1;
        } else if (i == 5) {
            deltaX = 2;
            deltaY = -1;
        } else if (i == 6) {
            deltaX = -2;
            deltaY = 1;
        } else if (i == 7) {
            deltaX = -2;
            deltaY = -1;
        }
        int checkX = getX() + deltaX;
        int checkY = getY() + deltaY;
        if (Boundary::inBounds(checkX, checkY)) {
            Piece* square = (*board)[checkX][checkY];
            if (square == nullptr) { // empty square
                getList()->addToFront(checkX, checkY, 0, false);
            } else {
                if (square->getColour() != getColour()) { // capture
                    getList()->addToFront(checkX, checkY, 0, true);
                }
            }
        }
    }
}
