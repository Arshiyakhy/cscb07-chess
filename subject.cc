#include "subject.h"
#include <algorithm>

void Subject::attach(Observer *o)
{
    observers.push_back(o);
}

void Subject::detach(Observer *o)
{
    observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
}

void Subject::notifyObservers(const Board &b) const
{
    for (Observer *o : observers)
        o->notify(b);
}