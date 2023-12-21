#include "subject.h"
void Subject::notifyObservers() {
    for (auto p : observers) {
        p->notify();
    }
}

void Subject::attach(Observer* o) {
    observers.emplace_back(o);
}
