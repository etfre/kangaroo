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
#include "../../include/search.h"

using namespace std;

TestClass::TestClass() {
	testDefaultSetup();
	testPin1();
	testMateInOne1();
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
}

//Test that we can pin black's rook to his king and win the exchange
void TestClass::testPin1() {
	S_BOARD b = createBitboards(testPinBoard1);
	Position pos(b, WHITE);
	S_MOVE move = search(pos, 4);
	assert(move.evaluation == 0);
	assert(move.toSquare == C4);
}

//Test for mate in one
void TestClass::testMateInOne1() {
	S_BOARD b = createBitboards(testMateInOneBoard1);
	Position pos(b, WHITE);
	S_MOVE move = search(pos, 1);
	// assert(move.evaluation == 10000);
	// assert(move.toSquare == H8);
}
