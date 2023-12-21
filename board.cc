#include "board.h"
Board::Board() {
    // nullify all pieces
    for (auto lt = begin(); lt != end(); ++lt) {
        *lt = nullptr;
    }
}

Piece* (*Board::getBoard())[8] {
    return board;
}

Board::~Board() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            delete board[i][j];
        }
    }
    whiteKing = nullptr;
    blackKing = nullptr;
    doubleMovedPawn = nullptr;
}

void Board::reNullify() {
    // nullify all pieces
    for (auto lt = begin(); lt != end(); ++lt) {
        delete *lt;
        *lt = nullptr;
    }
    whiteKing = nullptr;
    blackKing = nullptr;
    doubleMovedPawn = nullptr;
}

void Board::remove(int x, int y) {
    if (dynamic_cast<King*>(board[x][y]) != nullptr) {
        King* checkKing = dynamic_cast<King*>(board[x][y]);
        if (checkKing->getColour() == WHITE) {
            whiteKing = nullptr;
        } else {
            blackKing = nullptr;
        }
    }
    delete board[x][y];
    board[x][y] = nullptr;
}

King* Board::getWhiteKing() {
    return whiteKing;
}

King* Board::getBlackKing() {
    return blackKing;
}

void Board::setWhiteKing(King* whiteKing) {
    this->whiteKing = whiteKing;
}

void Board::setBlackKing(King* blackKing) {
    this->blackKing = blackKing;
}

void Board::linkRooks() {
    if (!whiteKing->canCastle()) {
        return;
    }

    Rook* checkRook = dynamic_cast<Rook*>(board[0][0]);
    if (checkRook != nullptr && checkRook->getColour() == WHITE) {
        whiteKing->attachLeftRook(checkRook);
        checkRook->enableCastle();
    }

    checkRook = dynamic_cast<Rook*>(board[7][0]);
    if (checkRook != nullptr && checkRook->getColour() == WHITE) {
        whiteKing->attachRightRook(checkRook);
        checkRook->enableCastle();
    }

    if (!blackKing->canCastle()) {
        return;
    }
    checkRook = dynamic_cast<Rook*>(board[0][7]);
    if (checkRook != nullptr && checkRook->getColour() == BLACK) {
        blackKing->attachLeftRook(checkRook);
        checkRook->enableCastle();
    }

    checkRook = dynamic_cast<Rook*>(board[7][7]);
    if (checkRook != nullptr && checkRook->getColour() == BLACK) {
        blackKing->attachRightRook(checkRook);
        checkRook->enableCastle();
    }
}

void Board::resetDoubleState() {
    if (doubleMovedPawn == nullptr) {
        return;
    }
    doubleMovedPawn->cancelDoubleState();
    doubleMovedPawn = nullptr;
}

void Board::trackDoubleState(Pawn* doubleMovedPawn) {
    this->doubleMovedPawn = doubleMovedPawn;
}

void Board::linkPawns(vector<Pawn*>& whitePawns, vector<Pawn*>& blackPawns) {
    for (auto p : whitePawns) {
        p->attachOpponentPawns(blackPawns);
    }

    for (auto p : blackPawns) {
        p->attachOpponentPawns(whitePawns);
    }
}

Board::Iterator Board::begin() {
    return Iterator(board, 0, 0);
};
    
Board::Iterator Board::end() {
    return Iterator(board, 0, 8);
};

Board::Board(Board& other) {
    // nullify all pieces
    for (auto lt = begin(); lt != end(); ++lt) {
        *lt = nullptr;
    }
    vector<Pawn*> whitePawns; // cannot directly copy opponentPawns due to circular pointers
    vector<Pawn*> blackPawns;
    for (auto lt = other.begin(); lt != other.end(); ++lt) {
        if (*lt == nullptr) {
            continue;
        }

        int x = (*lt)->getX();
        int y = (*lt)->getY();
        
        if (dynamic_cast<Pawn*>(*lt) != nullptr) {
            Pawn* copiedPawn = new Pawn(*dynamic_cast<Pawn*>(*lt));
            if (copiedPawn->isLastMoveDouble()) {
                doubleMovedPawn = copiedPawn;
            }
            if (copiedPawn->getColour() == WHITE) {
                whitePawns.emplace_back(copiedPawn);
            } else {
                blackPawns.emplace_back(copiedPawn);
            }
            board[x][y] = copiedPawn;
        } else if (dynamic_cast<Knight*>(*lt) != nullptr) {
            board[x][y] = new Knight(*dynamic_cast<Knight*>(*lt));
        } else if (dynamic_cast<Bishop*>(*lt) != nullptr) {
            board[x][y] = new Bishop(*dynamic_cast<Bishop*>(*lt));
        } else if (dynamic_cast<Queen*>(*lt) != nullptr) {
            board[x][y] = new Queen(*dynamic_cast<Queen*>(*lt));
        } else if (dynamic_cast<King*>(*lt) != nullptr) {
            King* copiedKing = new King(*dynamic_cast<King*>(*lt));
            board[x][y] = copiedKing;
            if (copiedKing->getColour() == WHITE) {
                whiteKing = copiedKing;
            } else {
                blackKing = copiedKing;
            }
        } else if (dynamic_cast<Rook*>(*lt) != nullptr) {
            board[x][y] = new Rook(*dynamic_cast<Rook*>(*lt));
        } else {
            throw InvalidElementException();
        }
        
        if (board[x][y] != nullptr) {
            board[x][y]->reNullify();
        }
    }

    if (whiteKing->canCastle()) {
        Rook* checkRook = dynamic_cast<Rook*>(board[0][0]);
        if (checkRook != nullptr && checkRook->eligibleToCastle()) {
            whiteKing->attachLeftRook(checkRook);
        }

        checkRook = dynamic_cast<Rook*>(board[7][0]);
        if (checkRook != nullptr && checkRook->eligibleToCastle()) {
            whiteKing->attachRightRook(checkRook);
        }
    }
    
    if (blackKing->canCastle()) {
        Rook* checkRook = dynamic_cast<Rook*>(board[0][7]);
        if (checkRook != nullptr && checkRook->eligibleToCastle()) {
            blackKing->attachLeftRook(checkRook);
        }

        checkRook = dynamic_cast<Rook*>(board[7][7]);
        if (checkRook != nullptr && checkRook->eligibleToCastle()) {
            blackKing->attachRightRook(checkRook);
        }
    }

    linkPawns(whitePawns, blackPawns);
}

Board::Board(Board&& other): whiteKing{other.whiteKing}, blackKing{other.blackKing}, doubleMovedPawn{other.doubleMovedPawn} {
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            board[x][y] = other.board[x][y];
            other.board[x][y] = nullptr;
        }
    }
    other.whiteKing = nullptr;
    other.blackKing = nullptr;
    other.doubleMovedPawn = nullptr;
}

Board& Board::operator=(Board& other) {
    if (this == &other) {
        return *this;
    }
    Board tmp = other;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            board[x][y] = tmp.board[x][y];
            tmp.board[x][y] = nullptr;
        }
    }
    whiteKing = tmp.whiteKing;
    blackKing = tmp.blackKing;
    doubleMovedPawn = tmp.doubleMovedPawn;
    tmp.whiteKing = nullptr;
    tmp.blackKing = nullptr;
    tmp.doubleMovedPawn = nullptr;
    return *this;
}

Board& Board::operator=(Board&& other) {
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            board[x][y] = other.board[x][y];
            other.board[x][y] = nullptr;
        }
    }
    whiteKing = other.whiteKing;
    blackKing = other.blackKing;
    doubleMovedPawn = other.doubleMovedPawn;
    other.whiteKing = nullptr;
    other.blackKing = nullptr;
    other.doubleMovedPawn = nullptr;
    return *this;
}
