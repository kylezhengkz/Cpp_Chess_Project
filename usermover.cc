#include "usermover.h"
void UserMover::moveUser(Board& board, istream& in, string squareOne, string squareTwo, int turn) {
    Piece* board2D[8][8];
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (board.getBoard()[x][y] == nullptr) {
                board2D[x][y] = nullptr;
            } else {
                board2D[x][y] = board.getBoard()[x][y];
            }
        }
    }
    int* startIndex = Boundary::stringSquareTo2DIndex(squareOne); // from square
    int* endIndex = Boundary::stringSquareTo2DIndex(squareTwo); // to square
        
    Piece* piece = board.getBoard()[startIndex[0]][startIndex[1]]; // piece from initial square
    if (!piece) {
        throw EmptySquareException(squareOne);
    } else if (piece->getColour() != turn) {
        throw WrongTurnException(turn);
    }

    // check if move is valid
    bool validMove = false;
    piece->generateMoves(&board2D);
    Move* move;
    for (auto lt = piece->getList()->begin(); lt != piece->getList()->end(); ++lt) { // iterate moves
        if ((*lt)->getNewX() == endIndex[0] && (*lt)->getNewY() == endIndex[1]) { // if new square matches
            validMove = true;
            move = *lt;
            break;
        }
    }

    if (!validMove) {
        throw InvalidMoveException(squareOne, squareTwo);
    }

    Move moveCopy(move->getNewX(), move->getNewY(), move->getVal(), move->isCapture(), nullptr);
    // clear move lists
    delete piece->getList();
    piece->reNullify();

    Board boardCopy = board;
    MoveImplementer::implementMove(boardCopy, true, in, boardCopy.getBoard()[piece->getX()][piece->getY()], moveCopy); // modify board state
    board = std::move(boardCopy); // will not execute if implementMove throws
}
