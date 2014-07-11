#include <string>
#include <vector>
#include <iostream>
#include <assert.h>
#include "../../include/defs.h"
#include "../../include/checks.h"
#include "../../include/tables.h"
#include "../../include/position.h"
#include "../../include/tests.h"
#include "../../include/testboards.h"

using namespace std;

TestClass::TestClass() {
	testDefaultSetup();
}

void TestClass::testDefaultSetup() {
	S_BOARD board = createBitboards(defaultBoard);
	assert(board.wR == SQUARES[A1] | SQUARES[H1]);
	assert(board.wN == SQUARES[B1] | SQUARES[G1]);
	assert(board.wB == SQUARES[C1] | SQUARES[F1]);	
	assert(board.wQ == SQUARES[D1]);
	assert(board.wK == SQUARES[E1]);
	assert(board.wP == RANK2);
	assert(board.bR == SQUARES[A8] | SQUARES[H8]);
	assert(board.bN == SQUARES[B8] | SQUARES[G8]);
	assert(board.bB == SQUARES[C8] | SQUARES[F8]);
	assert(board.bQ == SQUARES[D8]);
	assert(board.bK == SQUARES[E8]);
	assert(board.bP == RANK7);
	printBoard(board);
}

