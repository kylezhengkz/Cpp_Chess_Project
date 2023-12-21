#ifndef INVALIDMOVEEXCEPTION_H
#define INVALIDMOVEEXCEPTION_H
#include <stdexcept>
using namespace std;
class InvalidMoveException: public exception {
    string errorMessage;
  public:
    InvalidMoveException(string squareOne, string squareTwo);
    const char* what() const noexcept override;
};
#endif
