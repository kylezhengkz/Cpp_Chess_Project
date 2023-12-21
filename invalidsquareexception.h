#ifndef INVALIDSQUAREEXCEPTION_H
#define INVALIDSQUAREEXCEPTION_H
#include <stdexcept>
using namespace std;
class InvalidSquareException: public exception {
    string errorMessage;
  public:
    InvalidSquareException(string squareName);
    const char* what() const noexcept override;
};
#endif
