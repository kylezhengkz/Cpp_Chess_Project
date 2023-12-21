#include "invalidmoveexception.h"
InvalidMoveException::InvalidMoveException(string squareOne, string squareTwo):
errorMessage{squareOne + " to " + squareTwo + " is an invalid move"} {}
const char* InvalidMoveException::what() const noexcept {
    return errorMessage.c_str();
}
