#ifndef STALEMATEEXCEPTION_H
#define STALEMATEEXCEPTION_H
#include <stdexcept>
using namespace std;
class StalemateException: public exception {
    string errorMessage;
  public:
    StalemateException();
    const char* what() const noexcept override;
};
#endif
