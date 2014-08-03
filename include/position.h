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
	vector<U64> opponentAttackHistory;
	Position(S_BOARD b, string c);
	void makeMove(S_MOVE &move);
	void undoMove();
	void generatePossibleMoves();
	bool isCheck();
	bool kingEnPrise();
	bool isCheckmate();
	bool isStalemate();
	bool legalPosition();
	void handleCastling();
    void undoCastling();
    double evaluate();
    bool anyLegalMoves();
    void handlePromotion(S_MOVE);
};

#endif