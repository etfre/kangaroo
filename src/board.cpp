#include <string>
#include <iostream>
#include <assert.h>
#include "../include/defs.h"
#include "../include/checks.h"

using namespace std;

string testBoard = "_ _ _ _ k _ _ K"
                   "_ _ _ _ _ _ _ P"
                   "_ _ _ _ _ _ _ r"
                   "_ _ _ _ _ _ _ _"
                   "_ _ _ _ _ _ _ _"
                   "_ _ _ _ _ _ _ _"
                   "_ _ _ _ _ _ _ _"
                   "_ _ _ _ _ _ _ _"
                   ;

S_BOARD createBitboards(string stringBoard) {
	S_BOARD board;
	string spBoard;
	for (int i = 0; i <stringBoard.size(); i++) {
		if (stringBoard[i] != ' ') spBoard += stringBoard[i];
	}
	assert (spBoard.size() == 64);
	int flip;
	for (int i = 0; i < 64; i++) {
		flip = 7-2*(i%8);
		if (spBoard[63-i] == 'r') setBit(i+flip, board.wR);
		else if (spBoard[63-i] == 'n') setBit(i+flip, board.wN);
		else if (spBoard[63-i] == 'b') setBit(i+flip, board.wB);
		else if (spBoard[63-i] == 'q') setBit(i+flip, board.wQ);
		else if (spBoard[63-i] == 'k') setBit(i+flip, board.wK);
		else if (spBoard[63-i] == 'p') setBit(i+flip, board.wP);
		else if (spBoard[63-i] == 'R') setBit(i+flip, board.bR);
		else if (spBoard[63-i] == 'N') setBit(i+flip, board.bN);
		else if (spBoard[63-i] == 'B') setBit(i+flip, board.bB);
		else if (spBoard[63-i] == 'Q') setBit(i+flip, board.bQ);
		else if (spBoard[63-i] == 'K') setBit(i+flip, board.bK);
		else if (spBoard[63-i] == 'P') setBit(i+flip, board.bP);
		else (assert(spBoard[63-i] == '_'));
	}
	board.white = board.wR | board.wN | board.wB | board.wQ | board.wK | board.wP;
	board.black = board.bR | board.bN | board.bB | board.bQ | board.bK | board.bP;
	board.both = board.white | board.black;
	return board;
}

void movePiece(S_MOVE &move, S_BOARD &board, string color) {
	clearPiece(move.toSquare, board, switchColor(color));
	setAndClear(move.fromSquare, move.toSquare, *move.pieces, board, color);
}


void clearPiece(int square, S_BOARD &board, string color) {
	if (color == WHITE) {
		if (contains(square, board.wR)) clearBit(square, board.wR, board);
		else if (contains(square, board.wN)) clearBit(square, board.wN, board);
		else if (contains(square, board.wB)) clearBit(square, board.wB, board);
		else if (contains(square, board.wQ)) clearBit(square, board.wQ, board);
		else if (contains(square, board.wK)) clearBit(square, board.wK, board);
		else if (contains(square, board.wP)) clearBit(square, board.wP, board);
	}
	else {
		if (contains(square, board.bR)) clearBit(square, board.bR, board);
		else if (contains(square, board.bN)) clearBit(square, board.bN, board);
		else if (contains(square, board.bB)) clearBit(square, board.bB, board);
		else if (contains(square, board.bQ)) clearBit(square, board.bQ, board);
		else if (contains(square, board.bK)) clearBit(square, board.bK, board);
		else if (contains(square, board.bP)) clearBit(square, board.bP, board);
	}
}

void printBitboard(U64 bitBoard) {
	string board = toString(bitBoard);
	for (int i=0; i <= 56; i += 8) {
		for (int j=7; j >= 0; j--) {
			if (board[i+j] == '1') cout << 'x';
			else cout << '_';
			if (j != 0) cout << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void printBoard(S_BOARD board) {
	for (int i = 56; i >= 0; i -= 8) {
		for (int j = 0; j <= 7; j++) {
			if (contains(i+j, board.wR)) cout << "r ";
			else if (contains(i+j, board.wN)) cout << "n ";
			else if (contains(i+j, board.wB)) cout << "b ";
			else if (contains(i+j, board.wQ)) cout << "q ";
			else if (contains(i+j, board.wK)) cout << "k ";
			else if (contains(i+j, board.wP)) cout << "p ";
			else if (contains(i+j, board.bR)) cout << "R ";
			else if (contains(i+j, board.bN)) cout << "N ";
			else if (contains(i+j, board.bB)) cout << "B ";
			else if (contains(i+j, board.bQ)) cout << "Q ";
			else if (contains(i+j, board.bK)) cout << "K ";
			else if (contains(i+j, board.bP)) cout << "P ";
			else cout << "_ ";
		}
		cout << endl;
	}
	cout << endl;
	checkBoard(board);
}



