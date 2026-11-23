#ifndef COLOURDISPLAY_H
#define COLOURDISPLAY_H

#include <ostream>
#include "observer.h"

class ColourDisplay : public Observer
{
private:
    std::ostream &out;

public:
    explicit ColourDisplay(std::ostream &out) : out{out} {}
    void notify(const Board &b) override;
};

#endif