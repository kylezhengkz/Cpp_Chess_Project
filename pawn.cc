#include "pawn.h"
Pawn::Pawn(int x, int y, int colour): Piece{x, y, colour, 1} {}
Pawn::~Pawn() {}

bool Pawn::isMoved() {
    return moved;
}
bool Pawn::isLastMoveDouble() {
    return lastMoveDouble;
}

void Pawn::movePawn() {
    moved = true;
}

void Pawn::doubleMove() {
    lastMoveDouble = true;
}

void Pawn::cancelDoubleState() {
    lastMoveDouble = false;
}

Pawn* Pawn::getEnPassantPawn() {
    return enPassantPawn;
}

void Pawn::attachOpponentPawns(vector<Pawn*> opponentPawns) {
    this->opponentPawns = opponentPawns;
}

Pawn::Pawn(Pawn& other): Piece{other}, moved{other.moved}, lastMoveDouble{other.lastMoveDouble} {
    if (other.enPassantPawn != nullptr) {
        enPassantPawn = new Pawn(*(other.enPassantPawn));
    }
}

Pawn::Pawn(Pawn&& other):
Piece{other}, moved{other.moved}, lastMoveDouble{other.lastMoveDouble}, enPassantPawn{other.enPassantPawn} {
    other.enPassantPawn = nullptr;
}

Pawn& Pawn::operator=(Pawn& other) { // do not copy opponent pawns (circular pointers)
    Piece::operator=(other);
    moved = other.moved;
    lastMoveDouble = other.lastMoveDouble;
    if (other.enPassantPawn != nullptr) {
        enPassantPawn = new Pawn(*(other.enPassantPawn));
    }
    return *this;
}

Pawn& Pawn::operator=(Pawn&& other) {
    Piece::operator=(other);
    moved = other.moved;
    lastMoveDouble = other.lastMoveDouble;
    enPassantPawn = other.enPassantPawn;
    other.enPassantPawn = nullptr;
    return *this;
}

void Pawn::generateMoves(Piece* (*board)[8][8]) {
    int deltaY;
    if (getColour() == WHITE) {
        deltaY = 1;
    } else {
        deltaY = -1;
    }
    int checkX = getX();
    int checkY = getY() + deltaY;
    Piece* square = (*board)[checkX][checkY];
    if (square == nullptr) { // empty square
        getList()->addToFront(checkX, checkY, 0, false);
        if (!moved) { // check double move
            checkX = getX();
            checkY = getY() + 2*deltaY;
            square = (*board)[checkX][checkY];
            if (square == nullptr) {
                getList()->addToFront(checkX, checkY, 0, false);
            }
        }
    }

    // check captures
    checkY = getY() + deltaY;
    for (int i = 0; i < 2; i++) {
        if (i == 0) {
            checkX = getX() + 1;
        } else if (i == 1) {
            checkX = getX() - 1;
        }
        if (Boundary::inBounds(checkX, checkY)) {
            Piece* square = (*board)[checkX][checkY];
            if (square != nullptr && square->getColour() != getColour()) { // capture
                getList()->addToFront(checkX, checkY, 0, true);
            }
        }
    }

    // check en passant
    if (getColour() == WHITE) {
        checkY = 4;
    } else {
        checkY = 3;
    }

    if (getY() == checkY) {
        for (auto p : opponentPawns) {
            if ((p->isLastMoveDouble()) && (p->getY() == getY()) && (abs(p->getX() - getX()) == 1)) {
                enPassantPawn = p;
                getList()->addToFront(p->getX(), getY() + deltaY, 0, true);
                break;
            }
        }
    }
}
