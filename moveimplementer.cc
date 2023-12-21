#include "moveimplementer.h"
void promote(Piece*& piece, istream& in) { // promote pawn to a new piece
    cout << "Promote pawn to new piece by entering Q, R, N, OR B:" << endl;
    char newPiece;
    in >> newPiece;
    if (newPiece == 'Q') {
        Queen* queen = new Queen(piece->getX(), piece->getY(), piece->getColour());
        delete piece;
        piece = queen;
    } else if (newPiece == 'R') {
        Rook* rook = new Rook(piece->getX(), piece->getY(), piece->getColour());
        delete piece;
        piece = rook;
    } else if (newPiece == 'N') {
        Knight* knight = new Knight(piece->getX(), piece->getY(), piece->getColour());
        delete piece;
        piece = knight;
    } else if (newPiece == 'B') {
        Bishop* bishop = new Bishop(piece->getX(), piece->getY(), piece->getColour());
        delete piece;
        piece = bishop;
    } else {
        cout << "You can only promote to a queen, rook, knight, or bishop" << endl;
        promote(piece, in);
    }
}

void MoveImplementer::implementMove(Board& board, bool user, istream& in, Piece* piece, Move& move) { // modify board
    board.resetDoubleState();

    int newX = move.getNewX();
    int newY = move.getNewY();

    Pawn* pawn = dynamic_cast<Pawn*>(piece);
    if (move.isCapture()) { // check capture
        if (pawn != nullptr && pawn->getEnPassantPawn()) { // check en passant
            board.getBoard()[pawn->getEnPassantPawn()->getX()][pawn->getEnPassantPawn()->getY()] = nullptr;
            delete pawn->getEnPassantPawn();
        } else {
            delete board.getBoard()[newX][newY]; // remove piece from square
            board.getBoard()[newX][newY] = nullptr;
        }
    }

    if (pawn != nullptr) {
        pawn->movePawn();
        if (newY == 0 || newY == 7) {
            if (user) { // user pawn promotion
                promote(piece, in);
            } else { // always promotes to queen
                Queen* queen = new Queen(piece->getX(), piece->getY(), piece->getColour());
                delete piece;
                piece = queen;
            }
        } else if (abs(newY - piece->getY()) == 2) {
            pawn->doubleMove();
            board.trackDoubleState(pawn);
        }
    } else if (dynamic_cast<King*>(piece) != nullptr) {
        King* king = dynamic_cast<King*>(piece);
        king->moveKing();
        if (abs(newX - king->getX()) == 2) { // castle
            if (newX > king->getX()) { // RS Castling
                Rook* rightRook = dynamic_cast<Rook*>(king->getRightRook());
                board.getBoard()[rightRook->getX()][rightRook->getY()] = nullptr;
                board.getBoard()[newX - 1][newY] = rightRook;
                rightRook->setX(newX - 1);
                rightRook->setY(newY);
            } else { // LS Castling
                Rook* leftRook = dynamic_cast<Rook*>(king->getLeftRook());
                board.getBoard()[leftRook->getX()][leftRook->getY()] = nullptr;
                board.getBoard()[newX + 1][newY] = leftRook;
                leftRook->setX(newX + 1);
                leftRook->setY(newY);
            }
        }
    } else if (dynamic_cast<Rook*>(piece) != nullptr) {
        Rook* rook = dynamic_cast<Rook*>(piece);
        rook->moveRook();
    }

    // put piece in new square and update fields
    board.getBoard()[newX][newY] = piece;
    board.getBoard()[piece->getX()][piece->getY()] = nullptr;
    piece->setX(newX);
    piece->setY(newY);

    if (dynamic_cast<King*>(piece) != nullptr) {
        if (piece->getColour() == WHITE) {
            board.setWhiteKing(dynamic_cast<King*>(piece));
        } else {
            board.setBlackKing(dynamic_cast<King*>(piece));
        }
    }

    // check if move does not lead to check
    King* userKing;
    if (piece->getColour() == WHITE) {
        userKing = board.getWhiteKing();
    } else {
        userKing = board.getBlackKing();
    }

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

    if (!SafetyComputor::isSquareSafe(&board2D, userKing->getX(), userKing->getY(), -userKing->getColour())) {
        throw CheckException();
    }
}
