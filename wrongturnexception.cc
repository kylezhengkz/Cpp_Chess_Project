#include "wrongturnexception.h"
WrongTurnException::WrongTurnException(int turn) {
    if (turn == WHITE) {
        errorMessage = "It is white's turn";
    } else {
        errorMessage = "It is black's turn";
    }
}
const char* WrongTurnException::what() const noexcept {
    return errorMessage.c_str();
}
