#ifndef SUBJECT_H
#define SUBJECT_H
#include "observer.h"
#include <vector>
using namespace std;
class Observer;
class Subject {
  protected:
    vector<Observer*> observers;
  public:
    void notifyObservers();
    void attach(Observer* o);
};
#endif
