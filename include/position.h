#ifndef POSITION_H
#define POSITION_H
#include <vector>

#include "../include/defs.h"

using namespace std;

class Position
{
public:
    S_BOARD board;
	string color;
	int wKingCastle;
	int wQueenCastle;
	int bKingCastle;
	int bQueenCastle;
	int ply;
	vector<S_BOARD> boardHistory;
	vector<S_MOVE> possibleMoves;
	Position(S_BOARD b, string c);
	void makeMove(S_MOVE &move);
	void undoMove();
	void generatePossibleMoves();
	bool isCheck();
	bool isCheckmate();
	bool isStalemate();
	bool legalPosition();
	void handleCastling();
    void undoCastling();
    double evaluate();
};

#endif