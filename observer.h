#ifndef OBSERVER_H
#define OBSERVER_H

class Board;

// anything that wants to show the board after a real move
class Observer
{
public:
    virtual ~Observer() = default;
    virtual void notify(const Board &b) = 0;
};

#endif