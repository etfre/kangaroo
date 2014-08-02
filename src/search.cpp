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
	int bestScore = 0;
	bool bestMoveSet = false;
	if (!pos.anyLegalMoves()) {
		if (pos.isCheck()) {
			//CHECKMATE!!
			return 9999 * -colorInt;
		}
		else {
			//STALEMATE!!
			return 0;
		}
	}
	if (depth == 0) {
		return evaluate(pos);
	}
	pos.generatePossibleMoves();
	vector<S_MOVE> movesCopy = pos.possibleMoves;
	for (int i = 0; i < movesCopy.size(); i++) {
		pos.makeMove(movesCopy.at(i));
		if (!pos.kingEnPrise()) {
			double score = negamax(pos, depth-1, -colorInt);
			if (!bestMoveSet || pos.color == WHITE && score < bestScore ||
				pos.color == BLACK && score > bestScore) {
				bestMoveSet = true;
				bestScore = score;
			}
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
	bestMove.evaluation = 9999 * colorInt;
	bool bestMoveSet = false;
	if (pos.kingEnPrise()) {
		return bestMove;
	}
	vector<S_MOVE> movesCopy = pos.possibleMoves;
	for (int i = 0; i < movesCopy.size(); i++) {
		pos.makeMove(movesCopy.at(i));
		if (!pos.kingEnPrise()) {
			movesCopy[i].evaluation = negamax(pos, depth-1, colorInt);
			if (!bestMoveSet) {
				bestMove = movesCopy.at(i);
				bestMoveSet = true;
			}
			else if ((pos.color == BLACK && movesCopy.at(i).evaluation > bestMove.evaluation) ||
				(pos.color == WHITE && movesCopy.at(i).evaluation < bestMove.evaluation)) {
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
		}
	}
	return bestMove;
}