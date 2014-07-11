#include <iostream>
#include <string>
#include <assert.h>
#include "../include/defs.h"

using namespace std;

string switchColor(string color) {
	assert (color == WHITE || color == BLACK);
	if (color == WHITE) return BLACK;
	else if (color == BLACK) return WHITE;
}
