#ifndef EMPTYSQUAREEXCEPTION_H
#define EMPTYSQUAREEXCEPTION_H
#include <stdexcept>
using namespace std;
class EmptySquareException: public exception {
    string errorMessage;
  public:
    EmptySquareException(string squareName);
    const char* what() const noexcept override;
};
#endif
