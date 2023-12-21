#include "startposition.h"
void StartPosition::defaultStartingPosition(Board* currentPosition) {
    setupPawns(currentPosition);
    setupWhitePieces(currentPosition);
    setupBlackPieces(currentPosition);
    currentPosition->linkRooks();
}

void StartPosition::setupPawns(Board* currentPosition) {
    int y = 1;
    vector<Pawn*> whitePawns;
    for (int x = 0; x < 8; x++) {
        Pawn* pawn = new Pawn(x, y, WHITE);
        currentPosition->getBoard()[x][y] = pawn;
        whitePawns.emplace_back(pawn);
    }

    y = 6;
    vector<Pawn*> blackPawns;
    for (int x = 0; x < 8; x++) {
        Pawn* pawn = new Pawn(x, y, BLACK);
        currentPosition->getBoard()[x][y] = pawn;
        blackPawns.emplace_back(pawn);
    }

    currentPosition->linkPawns(whitePawns, blackPawns);
}

void StartPosition::setupWhitePieces(Board* currentPosition) {
    Rook* leftRook = new Rook(0, 0, WHITE);
    currentPosition->getBoard()[0][0] = leftRook;
    Rook* rightRook = new Rook(7, 0, WHITE);
    currentPosition->getBoard()[7][0] = rightRook;
    King* king = new King(4, 0, WHITE);
    currentPosition->getBoard()[4][0] = king;
    currentPosition->setWhiteKing(king);
    Queen* queen = new Queen(3, 0, WHITE);
    currentPosition->getBoard()[3][0] = queen;

    Bishop* leftBishop = new Bishop(2, 0, WHITE);
    currentPosition->getBoard()[2][0] = leftBishop;
    Knight* leftKnight = new Knight(1, 0, WHITE);
    currentPosition->getBoard()[1][0] = leftKnight;

    Bishop* rightBishop = new Bishop(5, 0, WHITE);
    currentPosition->getBoard()[5][0] = rightBishop;
    Knight* rightKnight = new Knight(6, 0, WHITE);
    currentPosition->getBoard()[6][0] = rightKnight;
}

void StartPosition::setupBlackPieces(Board* currentPosition) {
    Rook* leftRook = new Rook(0, 7, BLACK);
    currentPosition->getBoard()[0][7] = leftRook;
    Rook* rightRook = new Rook(7, 7, BLACK);
    currentPosition->getBoard()[7][7] = rightRook;
    King* king = new King(4, 7, BLACK);
    currentPosition->getBoard()[4][7] = king;
    currentPosition->setBlackKing(king);
    Queen* queen = new Queen(3, 7, BLACK);
    currentPosition->getBoard()[3][7] = queen;

    Bishop* leftBishop = new Bishop(2, 7, BLACK);
    currentPosition->getBoard()[2][7] = leftBishop;
    Knight* leftKnight = new Knight(1, 7, BLACK);
    currentPosition->getBoard()[1][7] = leftKnight;

    Bishop* rightBishop = new Bishop(5, 7, BLACK);
    currentPosition->getBoard()[5][7] = rightBishop;
    Knight* rightKnight = new Knight(6, 7, BLACK);
    currentPosition->getBoard()[6][7] = rightKnight;
}

void StartPosition::setup(istream& in, Board* currentPosition, ostream& out, TextDisplay* textDisplay, int& turn) {
    // + [piece initial] [square name]
    // - [square name]
    // = colour

    string setupLine;
    vector<Pawn*> whitePawns;
    vector<Pawn*> blackPawns;
    while (getline(in, setupLine)) {
        if (setupLine == "done" || setupLine == "DONE" || setupLine == "Done") {
            currentPosition->linkRooks();
            currentPosition->linkPawns(whitePawns, blackPawns);
            if (currentPosition->getWhiteKing() == nullptr) {
                throw NoKingException("White");
            } else if (currentPosition->getBlackKing() == nullptr) {
                throw NoKingException("Black");
            }
            break;
        }
        istringstream iss{setupLine};       

        string cmd; 
        if (!(iss >> cmd)) {
            out << "Invalid input" << endl;
            continue;
        } else if (cmd == "+") { // add piece
            string pieceInitial;
            if (!(iss >> pieceInitial)) {
                out << "Invalid input" << endl;
                continue;
            }
            string squareName;
            if (!(iss >> squareName)) {
                out << "Invalid input" << endl;
                continue;
            }
            
            int* square;
            try {
                square = Boundary::stringSquareTo2DIndex(squareName);
            } catch (exception& e) {
                cout << e.what() << endl;
                continue;
            }
            if (currentPosition->getBoard()[square[0]][square[1]] != nullptr) {
                out << squareName << " is already occupied. Please try again" << endl;
                continue;
            }

            if (pieceInitial == "P") {
                Pawn* newPawn = new Pawn(square[0], square[1], WHITE);
                whitePawns.emplace_back(newPawn);
                currentPosition->getBoard()[square[0]][square[1]] = newPawn;
            } else if (pieceInitial == "p") {
                Pawn* newPawn = new Pawn(square[0], square[1], BLACK);
                blackPawns.emplace_back(newPawn);
                currentPosition->getBoard()[square[0]][square[1]] = newPawn;
            } else if (pieceInitial == "N") {
                currentPosition->getBoard()[square[0]][square[1]] = new Knight(square[0], square[1], WHITE);
            } else if (pieceInitial == "n") {
                currentPosition->getBoard()[square[0]][square[1]] = new Knight(square[0], square[1], BLACK);
            } else if (pieceInitial == "B") {
                currentPosition->getBoard()[square[0]][square[1]] = new Bishop(square[0], square[1], WHITE);
            } else if (pieceInitial == "b") {
                currentPosition->getBoard()[square[0]][square[1]] = new Bishop(square[0], square[1], BLACK);
            } else if (pieceInitial == "R") {
                currentPosition->getBoard()[square[0]][square[1]] = new Rook(square[0], square[1], WHITE);
            } else if (pieceInitial == "r") {
                currentPosition->getBoard()[square[0]][square[1]] = new Rook(square[0], square[1], BLACK);
            } else if (pieceInitial == "Q") {
                currentPosition->getBoard()[square[0]][square[1]] = new Queen(square[0], square[1], WHITE);
            } else if (pieceInitial == "q") {
                currentPosition->getBoard()[square[0]][square[1]] = new Queen(square[0], square[1], BLACK);
            } else if (pieceInitial == "K") {
                if (currentPosition->getWhiteKing() != nullptr) {
                    out << "White king already exists on board" << endl;
                    continue;
                }
                King* newWhiteKing = new King(square[0], square[1], WHITE);
                if (square[0] != 4 || square[1] != 0) {
                    newWhiteKing->moveKing(); // doesn't actually move (removes castle eligibility)
                }
                currentPosition->getBoard()[square[0]][square[1]] = newWhiteKing;
                currentPosition->setWhiteKing(newWhiteKing);
            } else if (pieceInitial == "k") {
                if (currentPosition->getBlackKing() != nullptr) {
                    out << "Black king already exists on board" << endl;
                    continue;
                }
                King* newBlackKing = new King(square[0], square[1], BLACK);
                if (square[0] != 4 || square[1] != 7) {
                    newBlackKing->moveKing(); // doesn't actually move (removes castle eligibility)
                }
                currentPosition->getBoard()[square[0]][square[1]] = newBlackKing;
                currentPosition->setBlackKing(newBlackKing);
            } else {
                out << pieceInitial << " is not a valid piece initial" << endl;
                continue;
            }
            currentPosition->notifyObservers();
            out << textDisplay;
        } else if (cmd == "-") { // remove piece
            string squareName;
            if (!(iss >> squareName)) {
                out << "Invalid input" << endl;
                continue;
            }
            int* square;
            try {
                square = Boundary::stringSquareTo2DIndex(squareName);
            } catch (exception& e) {
                cout << e.what() << endl;
                continue;
            }
            currentPosition->remove(square[0], square[1]);
            currentPosition->notifyObservers();
            out << textDisplay;
        } else if (cmd == "=") {
            string colour;
            if (!(iss >> colour)) {
                out << "Invalid input" << endl;
                continue;
            }
            if (colour == "white" || colour == "WHITE" || colour == "White") {
                turn = WHITE;
            } else if (colour == "black" || colour == "BLACK" || colour == "Black") {
                turn = BLACK;
            } else {
                out << "Not a valid colour" << endl;
            }
        } else {
            out << "Invalid input" << endl;
            continue;
        }
    }
}
