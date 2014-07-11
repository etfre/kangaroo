#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include "../include/defs.h"
#include "../include/tables.h"
#include "../include/position.h"
#include "../include/checks.h"
#include "../include/search.h"
#include "../include/tests.h"

using namespace std;

int main() {
	// TestClass t;
	extern string testBoard;
	S_BOARD b = createBitboards(testBoard);
	Position pos(b, WHITE);
	S_MOVE move = search(pos, 2);
    return 0;
}





