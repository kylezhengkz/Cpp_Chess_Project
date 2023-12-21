#include "rook.h"
Rook::Rook(int x, int y, int colour): Piece{x, y, colour, 5} {}
Rook::~Rook() {}

bool Rook::eligibleToCastle() {
    return castleEligibility;
}

void Rook::enableCastle() {
    castleEligibility = true;
}

void Rook::moveRook() {
    castleEligibility = false;
}

Rook::Rook(Rook& other): Piece{other}, castleEligibility{other.castleEligibility} {}

Rook::Rook(Rook&& other): Piece{other}, castleEligibility{other.castleEligibility} {}

void Rook::generateMoves(Piece* (*board)[8][8]) {
    for (int i = 0; i < 4; i++) {
        int deltaX;
        int deltaY;
        if (i == 0) {
            deltaX = 0;
            deltaY = 1;
        } else if (i == 1) {
            deltaX = 1;
            deltaY = 0;
        } else if (i == 2) {
            deltaX = -1;
            deltaY = 0;
        } else if (i == 3) {
            deltaX = 0;
            deltaY = -1;
        }
        int checkX = getX() + deltaX;
        int checkY = getY() + deltaY;
        while (Boundary::inBounds(checkX, checkY)) {
            Piece* square = (*board)[checkX][checkY];
            if (square == nullptr) { // empty square
                getList()->addToFront(checkX, checkY, 0, false);
            } else {
                if (square->getColour() != getColour()) { // capture
                    getList()->addToFront(checkX, checkY, 0, true);
                }
                break;
            }
            checkX += deltaX;
            checkY += deltaY;
        }
    }
}
