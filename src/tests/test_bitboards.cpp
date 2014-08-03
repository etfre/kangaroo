#include <string>
#include <vector>
#include <iostream>
#include <assert.h>
#include "../../include/defs.h"
#include "../../include/checks.h"
#include "../../include/tables.h"
#include "../../include/position.h"
#include "../../include/tests/tests.h"
#include "../../include/tests/testboards.h"
#include "../../include/search.h"

using namespace std;

TestBitboards::TestBitboards() {
	testPromotion();
}

void TestBitboards::testPromotion() {
	S_BOARD b = createBitboards(testPromotionBoard1);
	Position pos(b, WHITE);
	for (int i = 0; i < pos.possibleMoves.size(); i++) {
		pos.makeMove(pos.possibleMoves.at(i));
		printBoard(pos.board);
		pos.undoMove();
	}
	// S_MOVE move = search(pos, 4);
	// assert(move.evaluation == 0);
	// assert(move.toSquare == C4);
}


