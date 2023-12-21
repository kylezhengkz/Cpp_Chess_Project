#include "bishop.h"
Bishop::Bishop(int x, int y, int colour): Piece{x, y, colour, 3.05} {}

Bishop::~Bishop() {}

Bishop::Bishop(Bishop& other): Piece{other} {}

Bishop::Bishop(Bishop&& other): Piece{other} {}

Bishop& Bishop::operator=(Bishop& other) {
    Piece::operator=(other);
    return *this;
}

Bishop& Bishop::operator=(Bishop&& other) {
    Piece::operator=(other);
    return *this;
}

void Bishop::generateMoves(Piece* (*board)[8][8]) {
    for (int i = 0; i < 4; i++) { // loop through each possible direction
        int deltaX; // directionX
        int deltaY; // directionY
        if (i == 0) {
            deltaX = 1;
            deltaY = 1;
        } else if (i == 1) {
            deltaX = 1;
            deltaY = -1;
        } else if (i == 2) {
            deltaX = -1;
            deltaY = 1;
        } else if (i == 3) {
            deltaX = -1;
            deltaY = -1;
        }
        // check future squares
        int checkX = getX() + deltaX;
        int checkY = getY() + deltaY;
        while (Boundary::inBounds(checkX, checkY)) { // within the board
            Piece* square = (*(board))[checkX][checkY];
            if (square == nullptr) { // empty square
                getList()->addToFront(checkX, checkY, 0, false); // add move
            } else { // square is occupied
                if (square->getColour() != getColour()) { // capture
                    getList()->addToFront(checkX, checkY, 0, true);
                }
                break; // halt
            }
            checkX += deltaX;
            checkY += deltaY;
        }
    }
}
