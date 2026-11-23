#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <ostream>
#include "observer.h"

class TextDisplay : public Observer
{
private:
    std::ostream &out;

public:
    explicit TextDisplay(std::ostream &out) : out{out} {}
    void notify(const Board &b) override;
};

#endif