#include "safetycomputor.h"
bool knightAttack(Piece* (*board)[8][8], int x, int y, int oppositionColour) {
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
        int checkX = x + deltaX;
        int checkY = y + deltaY;
        if (Boundary::inBounds(checkX, checkY)) {
            Piece* piece = (*board)[checkX][checkY];
            Knight* knight = dynamic_cast<Knight*>(piece);
            if (knight != nullptr && knight->getColour() == oppositionColour) {
                return false;
            }
        }
    }
    return true;
}

bool SafetyComputor::isSquareSafe(Piece* (*board)[8][8], int x, int y, int oppositionColour) {
    for (int i = 0; i < 8; i++) {
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
        } else if (i == 4) {
            deltaX = 1;
            deltaY = 1;
        } else if (i == 5) {
            deltaX = 1;
            deltaY = -1;
        } else if (i == 6) {
            deltaX = -1;
            deltaY = 1;
        } else if (i == 7) {
            deltaX = -1;
            deltaY = -1;
        }
        int checkX = x + deltaX;
        int checkY = y + deltaY;
        int iterations = 0;
        while (Boundary::inBounds(checkX, checkY)) {
            Piece* piece = (*board)[checkX][checkY];
            if (piece == nullptr) { // empty square
                checkX += deltaX;
                checkY += deltaY;
                ++iterations;
                continue;
            } else if (piece->getColour() != oppositionColour) { // same piece
                break;
            } else if (dynamic_cast<King*>(piece) != nullptr && iterations == 0) {
                return false;
            } else if (dynamic_cast<Pawn*>(piece) != nullptr && iterations == 0 && Direction::isDiagonal(deltaX, deltaY)
            && ((piece->getY() > y && oppositionColour == BLACK) || (piece->getY() < y && oppositionColour == WHITE))) {
                return false;
            } else if (dynamic_cast<Rook*>(piece) != nullptr && Direction::isStraight(deltaX, deltaY)) {
                return false;
            } else if (dynamic_cast<Bishop*>(piece) != nullptr && Direction::isDiagonal(deltaX, deltaY)) {
                return false;
            } else if (dynamic_cast<Queen*>(piece)) {
                return false;
            } else if (dynamic_cast<Knight*>(piece) != nullptr) { // knight (check later)
                break;
            } else {
                break;
            }
        }
    }
    return knightAttack(board, x, y, oppositionColour);
}
