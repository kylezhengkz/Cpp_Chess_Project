#ifndef INVALIDINPUTEXCEPTION_H
#define INVALIDINPUTEXCEPTION_H
#include <stdexcept>
using namespace std;
class InvalidInputException: public exception {
    string errorMessage;
  public:
    InvalidInputException();
    const char* what() const noexcept override;
};
#endif
