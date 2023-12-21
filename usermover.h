#ifndef USERMOVER_H
#define USERMOVER_H
#include <iostream>
#include <string>
#include "board.h"
#include "piece.h"
#include "emptysquareexception.h"
#include "invalidmoveexception.h"
#include "wrongturnexception.h"
#include <utility>
#include "moveimplementer.h"
using namespace std;
namespace UserMover {
    void moveUser(Board& board, istream& in, string squareOne, string squareTwo, int turn);
};
#endif
