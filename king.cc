#include "king.h"

char King::letter() const{return 'K';}
int King::value() const{return 1000;} //a king doesnt really have a value bc the game ends without it so we pick something really big