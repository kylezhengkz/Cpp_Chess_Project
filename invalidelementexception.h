#ifndef INVALIDELEMENTEXCEPTION_H
#define INVALIDELEMENTEXCEPTION_H
#include <stdexcept>
using namespace std;
class InvalidElementException: public exception {
    string errorMessage;
  public:
    InvalidElementException();
    const char* what() const noexcept override;
};
#endif
