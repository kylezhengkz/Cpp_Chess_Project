#include "textdisplay.h"
TextDisplay::TextDisplay(Board* board) {
    followBoard = board;
}

char TextDisplay::TextDisplay::pieceToChar(Piece* piece) {
    if (dynamic_cast<Pawn*>(piece) != nullptr) {
        return (piece->getColour() == WHITE) ? 'P' : 'p';
    } else if (dynamic_cast<Bishop*>(piece) != nullptr) {
        return (piece->getColour() == WHITE) ? 'B' : 'b';
    } else if (dynamic_cast<Knight*>(piece) != nullptr) {
        return (piece->getColour() == WHITE) ? 'N' : 'n';
    } else if (dynamic_cast<Rook*>(piece) != nullptr) {
        return (piece->getColour() == WHITE) ? 'R' : 'r';
    } else if (dynamic_cast<Queen*>(piece) != nullptr) {
        return (piece->getColour() == WHITE) ? 'Q' : 'q';
    } else if (dynamic_cast<King*>(piece) != nullptr) {
        return (piece->getColour() == WHITE) ? 'K' : 'k';
    } else {
        return '-';
    }
}

void TextDisplay::notify() {
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            charBoard[x][y] = pieceToChar(followBoard->getBoard()[x][y]);
        }
    }
}

TextDisplay::~TextDisplay() {};

void printLetterRow(ostream& out) {
    out << "  ";
    for (char c = 'A'; c <= 'H'; c++) {
        out << c;
    }
    out << endl;
}

void printDashRow(ostream& out) {
    out << "  ";
    for (int i = 0; i < 8; i++) {
        out << '-';
    }
    out << endl;
}

ostream& operator<<(ostream& out, TextDisplay* textDisplay) {
    
    printLetterRow(out);
    printDashRow(out);

    for (int y = 7; y >= 0; y--) {
        out << y + 1 << '|';
        for (int x = 0; x < 8; x++) {
            out << textDisplay->charBoard[x][y];
        }
        out << '|' << y + 1;
        out << endl;
    }

    printDashRow(out);
    printLetterRow(out);
    return out;
}
