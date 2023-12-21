#ifndef BOARD_H
#define BOARD_H
#include "subject.h"
#include "king.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "knight.h"
#include "queen.h"
#include "invalidelementexception.h"
#include <iostream>
class Piece;
class Pawn;
class King;
using namespace std;
class Board: public Subject {
    Piece* board[8][8];
    King* whiteKing = nullptr;
    King* blackKing = nullptr;
    Pawn* doubleMovedPawn = nullptr; // only one pawn can have double state move at a time
  public:
    Board();
    Piece* (*getBoard())[8];
    ~Board();
    void reNullify();
    void remove(int x, int y);
    King* getWhiteKing();
    King* getBlackKing();
    void setWhiteKing(King* whiteKing);
    void setBlackKing(King* blackKing);
    void linkRooks();
    void resetDoubleState();
    void trackDoubleState(Pawn* doubleMovedPawn);
    void linkPawns(vector<Pawn*>& whitePawns, vector<Pawn*>& blackPawns);
    Board(Board& other);
    Board(Board&& other);
    Board& operator=(Board& other);
    Board& operator=(Board&& other);
    class Iterator {
	      Piece* (*board)[8];
        int x;
        int y;
      public:
	      Iterator(Piece* (*board)[8], int x, int y): board{board}, x{x}, y{y} {}
	      Piece*& operator*() {
          return board[x][y];
        }
			
	      Iterator& operator++() {
            x++;
            if (x > 7) {
                x = 0;
                y++;
            }
		        return *this;
	      }

	      bool operator!=(const Iterator& other) const {
		        return (x != other.x) || (y != other.y);
	      }
    };

    Iterator begin();
    Iterator end();
};
#endif
