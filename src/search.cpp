#include <string>
#include <vector>
#include <iostream>
#include <assert.h>
#include "../include/defs.h"
#include "../include/checks.h"
#include "../include/position.h"
#include "../include/evaluate.h"

using namespace std;

double negamax(Position &pos, int depth, int colorInt) {
	printBoard(pos.board);
	int bestScore = -9999;
	if (depth == 0) {
		return colorInt * evaluate(pos);
	}
	pos.generatePossibleMoves();
	vector<S_MOVE> movesCopy = pos.possibleMoves;
	for (int i = 0; i < movesCopy.size(); i++) {
		pos.makeMove(movesCopy[i]);
		// if (pos.legalPosition()) {
			int score = -negamax(pos, depth-1, -colorInt);
			if (score > bestScore) bestScore = score;
		// }
		pos.undoMove();
	}
	return bestScore;
}

S_MOVE search(Position &pos, int depth) {
	assert(depth >= 1);
	int colorInt;
	if (pos.color == WHITE) colorInt = BCOLOR;
	else colorInt = WCOLOR;
	S_MOVE bestMove;
	bestMove.fromSquare = 0ULL;
	bool bestMoveSet = false;
	if (!pos.legalPosition()) {
		cout << "Illegal start Position!!" << endl;
		return bestMove;
	}
	vector<S_MOVE> movesCopy = pos.possibleMoves;
	for (int i = 0; i < movesCopy.size(); i++) {
		pos.makeMove(movesCopy[i]);
		// if (pos.legalPosition()) {
			movesCopy[i].evaluation = negamax(pos, depth-1, colorInt);
			if (!bestMoveSet) {
				bestMove = movesCopy[i];
				bestMoveSet = true;
			}
			else if ((pos.color == BLACK && movesCopy[i].evaluation > bestMove.evaluation) ||
				(pos.color == WHITE && movesCopy[i].evaluation < bestMove.evaluation)) {
				bestMove = movesCopy[i];
			}
		// }
		// cout << "Best move: " << bestMove.evaluation << endl;
		// cout << "Current move: " << pos.possibleMoves[i].evaluation << endl << endl;	
		pos.undoMove();
	}
	if (!bestMoveSet) cout << "Position is already checkmate!!" << endl;
	return bestMove;
}