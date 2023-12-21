#include "checkexception.h"
CheckException::CheckException(): errorMessage{"This move leaves the king in check"} {}
const char* CheckException::what() const noexcept {
    return errorMessage.c_str();
}
