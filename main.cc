#include <iostream>
#include <string>
#include "position.h"
#include "colour.h"
#include "piece.h"
#include "king.h"
using namespace std;

int main(){
    King king(Colour::WHITE);
    cout << "King symbol: " << king.symbol() << std::endl;
    King blackKing(Colour::BLACK);
    cout << "Black King symbol: " << blackKing.symbol() << std::endl;
    return 0;
}