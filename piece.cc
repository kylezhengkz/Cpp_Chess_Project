#include "piece.h"
Piece::Piece(int x, int y, int colour, double value): x{x}, y{y}, colour{colour}, value{value}, moveList{new MoveList()} {}

void Piece::reNullify() {
    moveList = new MoveList();
}

Piece::~Piece() {}

int Piece::getX() {
    return x;
}
int Piece::getY() {
    return y;
}

void Piece::setX(int x) {
    this->x = x;
}

void Piece::setY(int y) {
    this->y = y;
}

double Piece::getValue() {
    return value;
}

int Piece::getColour() {
    return colour;
}
MoveList* Piece::getList() {
    return moveList;
}

Piece::Piece(Piece& other): x{other.x}, y{other.y}, colour{other.colour}, value{other.value} {}

Piece::Piece(Piece&& other): x{other.x}, y{other.y}, colour{other.colour}, value{other.value} {}

Piece& Piece::operator=(Piece& other) {
    if (this == &other) {
        return *this;
    }
    x = other.x;
    y = other.y;
    colour = other.colour;
    value = other.value;
    return *this;
}

Piece& Piece::operator=(Piece&& other) {
    x = other.x;
    y = other.y;
    colour = other.colour;
    value = other.value;
    return *this;
}

