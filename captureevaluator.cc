#include "captureevaluator.h"
CaptureEvaluator::CaptureEvaluator(Computer* next): ComputerDecorator{next} {}

double materialBalance(Board* currentPosition, int colour) {
    double val = 0;
    for (auto p : *currentPosition) {
        if (p == nullptr) {
            continue;
        }
        if (p->getColour() == colour) {
            val += p->getValue();
        } else {
            val -= p->getValue();
        }
    }
    return val;
}

void CaptureEvaluator::selectBestMove() {
    map<Board*, double>* receivedPositions = CaptureEvaluator::evalMoves();
    Board* bestPosition = receivedPositions->begin()->first;
    double highestValue = receivedPositions->begin()->second;
    for (auto& it : *receivedPositions) {
        Board* newPosition = it.first;
        double& value = it.second;
        if (value > highestValue) {
            bestPosition = newPosition;
            highestValue = value;
        }
    }
    CaptureEvaluator::setBoard(bestPosition);
}

map<Board*, double>* CaptureEvaluator::evalMoves(){
    map<Board*, double>* receivedPositions = next->evalMoves();
    Board* board = next->getBoard();
    int colour = next->getColour();

    for (auto& it : *receivedPositions) {
        Board* newPosition = it.first;
        double& value = it.second;
        value += (materialBalance(newPosition, colour) - materialBalance(board, colour));
    }
    return receivedPositions;
}

Board* CaptureEvaluator::getBoard() { return next->getBoard(); }
    
int CaptureEvaluator::getColour() { return next->getColour(); }

void CaptureEvaluator::setBoard(Board* newPosition) {
    next->setBoard(newPosition);
}
