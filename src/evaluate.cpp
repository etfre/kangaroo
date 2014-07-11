
#include <iostream>
#include "../include/defs.h"
#include "../include/position.h"

using namespace std;

double evaluate(Position pos) {
	short wRCount = popCount(pos.board.wR);
	short wNCount = popCount(pos.board.wN);
	short wBCount = popCount(pos.board.wB);
	short wQCount = popCount(pos.board.wQ);
	short wKCount = popCount(pos.board.wK);
	short wPCount = popCount(pos.board.wP);
	short bRCount = popCount(pos.board.bR);
	short bNCount = popCount(pos.board.bN);
	short bBCount = popCount(pos.board.bB);
	short bQCount = popCount(pos.board.bQ);
	short bKCount = popCount(pos.board.bK);
	short bPCount = popCount(pos.board.bP);
	double score = (wQCount-bQCount) * 9 + (wRCount-bRCount) * 5 + (wBCount-bBCount) * 3 + (wNCount-bNCount) * 3 + (wPCount-bPCount);
	return score;
}