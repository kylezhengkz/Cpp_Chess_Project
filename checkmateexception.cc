#include "checkmateexception.h"
CheckmateException::CheckmateException(): errorMessage{"Checkmate"} {}
const char* CheckmateException::what() const noexcept {
    return errorMessage.c_str();
}
