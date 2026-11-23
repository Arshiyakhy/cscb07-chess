#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "observer.h"

class Subject
{
private:
    std::vector<Observer *> observers;   // NOT owned: the Controller owns the displays

public:
    virtual ~Subject() = default;
    void attach(Observer *o);
    void detach(Observer *o);
    void notifyObservers(const Board &b) const;
};

#endif