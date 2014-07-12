#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <assert.h>
#include "../include/defs.h"
#include "../include/checks.h"
#include "../include/tables.h"
#include "../include/position.h"

using namespace std;

Position::Position(S_BOARD b, string c) {
	board = b;
	color = c;
	ply = 0;
	/* Castling permissions start at 0, meaning that they are valid. Once 
	permission is lost (due to castling or king/respective rook moving), value
	is set to the ply on which castling permission was lost. Set during makeMove
	and unset during undoMove. */
	wKingCastle = 0;
	wQueenCastle = 0;
	bKingCastle = 0;
	bQueenCastle = 0;
	boardHistory.push_back(board);
	vector<S_MOVE> possibleMoves;
	generatePossibleMoves();
}

void Position::makeMove(S_MOVE &move) {
	ply++;
	movePiece(move, board, color);
	handleCastling();
	boardHistory.push_back(board);
	color = switchColor(color);
}

void Position::undoMove() {
	ply--;
	boardHistory.pop_back();
	board = boardHistory.at(boardHistory.size()-1);
	undoCastling();
	color = switchColor(color);
}

void Position::generatePossibleMoves() {
	possibleMoves.clear();
	assert(color == WHITE || color == BLACK);
	if (color == WHITE) {
		generatePieceMoves(possibleMoves, board, board.wR, WHITE, generateRookMoves);
		generatePieceMoves(possibleMoves, board, board.wN, WHITE, generateKnightMoves);
		generatePieceMoves(possibleMoves, board, board.wB, WHITE, generateBishopMoves);
		generatePieceMoves(possibleMoves, board, board.wQ, WHITE, generateQueenMoves);
		generatePieceMoves(possibleMoves, board, board.wK, WHITE, generateKingMoves);
		generatePieceMoves(possibleMoves, board, board.wP, WHITE, generatePawnMoves);
	}
	else if (color == BLACK) {
		generatePieceMoves(possibleMoves, board, board.bR, BLACK, generateRookMoves);
		generatePieceMoves(possibleMoves, board, board.bN, BLACK, generateKnightMoves);
		generatePieceMoves(possibleMoves, board, board.bB, BLACK, generateBishopMoves);
		generatePieceMoves(possibleMoves, board, board.bQ, BLACK, generateQueenMoves);
		generatePieceMoves(possibleMoves, board, board.bK, BLACK, generateKingMoves);
		generatePieceMoves(possibleMoves, board, board.bP, BLACK, generatePawnMoves);
	}
}

bool Position::isCheck() {
	// if it's a player's turn and their king is attacked
	if ((color == WHITE && board.wK & getAttacks(board, BLACK)) ||
		(color == BLACK && board.bK & getAttacks(board, WHITE))) return true;
	return false;
}

bool Position::isCheckmate() {
	// if ((color == WHITE && board.wK & getAttacks(board, BLACK)) ||
	// 	(color == BLACK && board.bK & getAttacks(board, WHITE))) return true;
	// return false;
	U64 king;
	if (color == WHITE) king = board.bK;
	else king = board.wK;
	return true;
}


bool Position::legalPosition() {
	/*
	Check whether the current position on the board is legal. Color refers to the player
	who moves next, ie if white has just moved, color will be black.
	*/
	U64 king;
	if (color == WHITE) king = board.bK;
	else king = board.wK;
	U64 attacks = getAttacks(board, color);
	if (attacks & king) return false;
	// if (ply > 0) {
	// 	if (wKingCastle == ply && ((SQUARES[E1] | SQUARES[F1]) & attacks)) return false;
	// 	else if (wQueenCastle == ply && ((SQUARES[E1] | SQUARES[D1]) & attacks)) return false;
	// 	else if (bKingCastle == ply && ((SQUARES[E8] | SQUARES[F8]) & attacks)) return false;
	// 	else if (bQueenCastle == ply && ((SQUARES[E8] | SQUARES[D8]) & attacks)) return false;
	// }
	return true;
}


void Position::handleCastling() {
	/*
	Disable castling permissions and move rook if applicable. Do *NOT* check
	for castling legality here!
	*/
	if (color == WHITE) {
		if (wKingCastle == 0 && SQUARES[G1] & board.wK && contains(H1, board.wR)) {
			clearBit(H1, board.wR, board);
			setBit(F1, board.wR, board, WHITE);
			wKingCastle = ply;
		}
		else if (wQueenCastle == 0 && SQUARES[C1] & board.wK && contains(A1, board.wR)) {
			clearBit(A1, board.wR, board);
			setBit(D1, board.wR, board, WHITE);
			wQueenCastle = ply;
		}
	}
	else {
		if (bKingCastle == 0 && SQUARES[G8] & board.bK && contains(H8, board.bR)) {
			cout << ply << endl;
			clearBit(H8, board.bR, board);
			setBit(F8, board.bR, board, BLACK);
			bKingCastle = ply;
		}
		else if (bQueenCastle == 0 && SQUARES[C8] & board.bK && contains(A8, board.bR)) {
			clearBit(A8, board.bR, board);
			setBit(D8, board.bR, board, BLACK);
			bQueenCastle = ply;
		}
	}
}

void Position::undoCastling() {
	if (ply == wKingCastle) wKingCastle = 0;
	else if (ply == wQueenCastle) wQueenCastle = 0;
	else if (ply == bKingCastle) bKingCastle = 0;
	else if (ply == bQueenCastle) bQueenCastle = 0;
}