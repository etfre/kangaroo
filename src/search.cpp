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
	int bestScore = 10000;
	// if (!pos.anyLegalMoves()) {
	// 	cout << "TRACE" << endl;
	// }
	if (pos.isStalemate()) {
		return 0;
	}
	if (pos.isCheck()) {

	}

	if (depth == 0) {
		return evaluate(pos);
	}
	pos.generatePossibleMoves();
	vector<S_MOVE> movesCopy = pos.possibleMoves;
	for (int i = 0; i < movesCopy.size(); i++) {
		pos.makeMove(movesCopy[i]);
		if (pos.legalPosition()) {
			double score = negamax(pos, depth-1, -colorInt);
			if (bestScore == 10000 || pos.color == WHITE && score < bestScore ||
				pos.color == BLACK && score > bestScore) bestScore = score;
		}
		pos.undoMove();
	}
	return bestScore;
}

S_MOVE search(Position &pos, int depth) {
	assert(depth >= 1);
	int colorInt = -1;
	if (pos.color == BLACK) colorInt = 1;
	S_MOVE bestMove;
	bestMove.fromSquare = -1;
	bestMove.evaluation = 10000 * colorInt;
	bool bestMoveSet = false;
	if (!pos.legalPosition()) {
		return bestMove;
	}
	vector<S_MOVE> movesCopy = pos.possibleMoves;
	for (int i = 0; i < movesCopy.size(); i++) {
		pos.makeMove(movesCopy[i]);
		if (pos.legalPosition()) {
			movesCopy[i].evaluation = negamax(pos, depth-1, colorInt);
			if (!bestMoveSet) {
				bestMove = movesCopy.at(i);
				bestMoveSet = true;
			}
			else if ((pos.color == BLACK && movesCopy[i].evaluation > bestMove.evaluation) ||
				(pos.color == WHITE && movesCopy[i].evaluation < bestMove.evaluation)) {
				bestMove = movesCopy.at(i);
			}
		}
		// cout << "Best move: " << bestMove.evaluation << endl;
		// cout << "Current move: " << movesCopy[i].evaluation << endl << endl;	
		pos.undoMove();
	}
	if (!bestMoveSet) {
		if (pos.isCheck());
		else {
			bestMove.evaluation = 0;
			// cout << "Position is already stalemate!!" << endl;
		}
	}
	return bestMove;
}