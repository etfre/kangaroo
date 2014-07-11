#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include "../include/position.h"

using namespace std;

double negamax(Position &pos, int depth, int colorInt);
S_MOVE search(Position &pos, int depth);

#endif