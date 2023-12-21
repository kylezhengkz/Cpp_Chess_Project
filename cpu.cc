#include "cpu.h"
#include "randomdecimal.h"
CPU::CPU(Board* board, int* colour): board(board), colour{colour} {}

int getRandomNumber(int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, size - 1);
    return dis(gen);
}

void CPU::selectBestMove() {
    map<Board*, double>* receivedPositions = CPU::evalMoves();
    int index = getRandomNumber((*receivedPositions).size());
    auto it = next(receivedPositions->begin(), index); // point to the selected element
    *board = *(it->first);
}

map<Board*, double>* CPU::evalMoves() {
    (*newPositions).clear();
    Piece* board2D[8][8];
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (board->getBoard()[x][y] == nullptr) {
                board2D[x][y] = nullptr;
            } else {
                board2D[x][y] = board->getBoard()[x][y];
            }
        }
    }

    // generate moves
    // implement each move in a board copy
    // remove illegal board positions
    //      if none remain, then checkmate (or stalemate)
    // static eval current board - static eval new board
    // for capture, evaluate difference in material balance
    
    King* checkKing;
    for (auto p : *board) {
        if (p != nullptr && p->getColour() == *colour) {
            if (dynamic_cast<King*>(p)) {
                checkKing = dynamic_cast<King*>(p);
            }
            p->generateMoves(&board2D);
            for (auto m : *(p->getList())) {
                Board boardCopy = *board;
                stringstream dummyStream("dummy istream");
                try {
                    MoveImplementer::implementMove(boardCopy, false, dummyStream, boardCopy.getBoard()[p->getX()][p->getY()], *m);
                    Board* newPosition = new Board();
                    *newPosition = move(boardCopy);
                    (*newPositions)[newPosition] = RandomDecimal::generateRandomDecimal();
                } catch (exception& e) {
                    continue;
                }
            }
            // clear piece's move list
            delete p->getList();
            p->reNullify();
        }
    }

    if (newPositions->empty()) {
        bool checkmate = !SafetyComputor::isSquareSafe(&board2D, checkKing->getX(), checkKing->getY(), -checkKing->getColour());
        if (checkmate) {
            throw CheckmateException();
        } else {
            throw StalemateException();
        }
    }

    return newPositions;
}

Board* CPU::getBoard() { return board; }
    
int CPU::getColour() { return *colour; }

void CPU::setBoard(Board* newPosition) {
    *board = *newPosition;
}
