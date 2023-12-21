#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include "observer.h"
#include "constants.h"
#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"
#include <iostream>
class TextDisplay: public Observer {
    Board* followBoard;
    char charBoard[8][8] = {
        {'-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-'}
    };
    char pieceToChar(Piece* piece);
  public:
    TextDisplay(Board* board);
    void notify();
    ~TextDisplay();
    friend ostream& operator<<(ostream& out, TextDisplay* textDisplay);
};
#endif
