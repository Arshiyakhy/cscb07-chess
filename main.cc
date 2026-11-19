#include <iostream>
#include <string>
#include "position.h"
#include "colour.h"

int main(){
    std::string tests[] = {"a1", "h8", "e4", "d5", "z9", "a0", "i3", "b10", "c-1", "g7"};
    for (const auto &test : tests){
        Position pos = Position::fromString(test);
        if (pos.inBounds()){    
            std::cout << test << " is in bounds at (" << pos.row << ", " << pos.col << ")\n";
        } else {
            std::cout << test << " is out of bounds\n";
        }
    }
    return 0;
}