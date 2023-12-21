#include "emptysquareexception.h"
EmptySquareException::EmptySquareException(string squareName): errorMessage{squareName + " is an empty square"} {}
const char* EmptySquareException::what() const noexcept {
    return errorMessage.c_str();
}
