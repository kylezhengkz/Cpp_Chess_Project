#include "invalidsquareexception.h"
InvalidSquareException::InvalidSquareException(string squareName):
errorMessage{squareName + " is an invalid square"} {}
const char* InvalidSquareException::what() const noexcept {
    return errorMessage.c_str();
}
