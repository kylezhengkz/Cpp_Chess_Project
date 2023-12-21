#include "invalidelementexception.h"
InvalidElementException::InvalidElementException(): errorMessage{"There is an element on the board that is neither empty square or piece"} {}
const char* InvalidElementException::what() const noexcept {
    return errorMessage.c_str();
}
