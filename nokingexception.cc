#include "nokingexception.h"
NoKingException::NoKingException(string colour):
errorMessage{"You cannot start the game without a " + colour + " king"} {}
const char* NoKingException::what() const noexcept {
    return errorMessage.c_str();
}
