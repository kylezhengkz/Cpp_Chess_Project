#include "stalemateexception.h"
StalemateException::StalemateException(): errorMessage{"Stalement"} {}
const char* StalemateException::what() const noexcept {
    return errorMessage.c_str();
}
