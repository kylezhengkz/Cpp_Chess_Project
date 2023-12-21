#ifndef CHECKEXCEPTION_H
#define CHECKEXCEPTION_H
#include <stdexcept>
using namespace std;
class CheckException: public exception {
    string errorMessage;
  public:
    CheckException();
    const char* what() const noexcept override;
};
#endif
