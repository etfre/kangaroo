#include <vector>
#include <map>
#include <iostream>
#include <assert.h>
#include "../include/defs.h"
#include "../include/tables.h"

using namespace std;

void generatePieceMoves(vector<S_MOVE> &possibleMoves, S_BOARD board, U64 &pieces, string color, U64 (*genFunc)(int, S_BOARD&, string, bool)){
	U64 piecesCopy = pieces;
	while (piecesCopy != 0) {
		int square = bitScanForward(piecesCopy);
		U64 movesBitboard = genFunc(square, board, color, false);
		vector<int> toSquares = toSquaresfromBitboard(movesBitboard);
		for (int i = 0; i < toSquares.size(); i++) {
			S_MOVE move;
			move.pieces = &pieces;
			move.fromSquare = square;
			move.toSquare = toSquares.at(i);
			move.promoteTo = "";
			if ((color == WHITE && move.toSquare > 55 && contains(move.fromSquare, board.wP)) ||
				(color == BLACK && move.toSquare < 8 && contains(move.fromSquare, board.bP))) {
				addPromotionMoves(possibleMoves, move);
			}
			else possibleMoves.push_back(move);
		}
		clearBit(square, piecesCopy);
	}
}

void addPromotionMoves(vector<S_MOVE> &possibleMoves, S_MOVE move) {
	vector<string> promotionPieces = {"knight", "bishop", "rook", "queen"};
	for (int i = 0; i < 4; i++) {
		S_MOVE newMove = move;
		newMove.promoteTo = promotionPieces.at(i);
		possibleMoves.push_back(newMove);
	}
}

U64 generatePawnMoves(int square, S_BOARD &board, string color, bool includeAttacks) {
	U64 moves;
	U64 attacks;
	if (color == WHITE) {
		moves = whitePawnStraightMoves[square] & ~board.black;
		if (moves != whitePawnStraightMoves[square]) moves &= ~RANK4;
		attacks = whitePawnAttacks[square] & board.black;
	}
	if (color == BLACK) {
		moves = blackPawnStraightMoves[square] & ~board.white;
		if (moves != blackPawnStraightMoves[square]) moves &= ~RANK5;
		attacks = blackPawnAttacks[square] & board.white;
	}
	return moves | attacks;
}

U64 generateKnightMoves(int square, S_BOARD &board, string color, bool includeAttacks) {
	if (includeAttacks) return knightMoves[square];
	if (color == WHITE) return knightMoves[square] & ~board.white;
	else return knightMoves[square] & ~board.black;
}

U64 generateRookMoves(int square, S_BOARD &board, string color, bool includeAttacks) {
	U64 north = getRayAttacks(square, rayAttacks[N], board, POSITIVE, includeAttacks);
	U64 east = getRayAttacks(square, rayAttacks[E], board, POSITIVE, includeAttacks);
	U64 south = getRayAttacks(square, rayAttacks[S], board, NEGATIVE, includeAttacks);
	U64 west = getRayAttacks(square, rayAttacks[W], board, NEGATIVE, includeAttacks);
	return north | east | south | west;
}

U64 generateBishopMoves(int square, S_BOARD &board, string color, bool includeAttacks) {
	U64 northeast = getRayAttacks(square, rayAttacks[NE], board, POSITIVE, includeAttacks);
	U64 southeast = getRayAttacks(square, rayAttacks[SE], board, NEGATIVE, includeAttacks);
	U64 southwest = getRayAttacks(square, rayAttacks[SW], board, NEGATIVE, includeAttacks);
	U64 northwest = getRayAttacks(square, rayAttacks[NW], board, POSITIVE, includeAttacks);
	return northeast | southeast | southwest | northwest;
}

U64 generateQueenMoves(int square, S_BOARD &board, string color, bool includeAttacks) {
	U64 north = getRayAttacks(square, rayAttacks[N], board, POSITIVE, includeAttacks);
	U64 northeast = getRayAttacks(square, rayAttacks[NE], board, POSITIVE, includeAttacks);
	U64 east = getRayAttacks(square, rayAttacks[E], board, POSITIVE, includeAttacks);
	U64 southeast = getRayAttacks(square, rayAttacks[SE], board, NEGATIVE, includeAttacks);
	U64 south = getRayAttacks(square, rayAttacks[S], board, NEGATIVE, includeAttacks);
	U64 southwest = getRayAttacks(square, rayAttacks[SW], board, NEGATIVE, includeAttacks);
	U64 west = getRayAttacks(square, rayAttacks[W], board, NEGATIVE, includeAttacks);
	U64 northwest = getRayAttacks(square, rayAttacks[NW], board, POSITIVE, includeAttacks);
	return north | northeast | east | southeast | south | southwest | west | northwest;
}

U64 generateKingMoves(int square, S_BOARD &board, string color, bool includeAttacks) {
	// Does *not* account for check or castling legality
	if (includeAttacks) return kingMoves[square];
	U64 moves;
	if (color == WHITE) {
		moves = kingMoves[square] & ~board.white;
		if (square == E1 && !contains(F1, board.both) && !contains(G1, board.both) && contains(H1, board.wR)) setBit(G1, moves);
		else if (square == E1 && !contains(D1, board.both) && !contains(C1, board.both) && !contains(B1, board.both) && contains(A1, board.wR)) setBit(C1, moves);
	}
	if (color == BLACK) {
		moves = kingMoves[square] & ~board.black;
		if (square == E8 && !contains(F8, board.both) && !contains(G8, board.both) && contains(H8, board.bR)) setBit(G8, moves);
		else if (square == E8 && !contains(D8, board.both) && !contains(C8, board.both) && !contains(B8, board.both) && contains(A1, board.bR)) setBit(C8, moves);
	}
	return moves;
}

U64 getRayAttacks(int square, const U64 initialAttacks[64], S_BOARD &board, string direction, bool includeAttacks) {
	/* 
	Implement classical approach for generating sliding moves. See:
	http://chessprogramming.wikispaces.com/Classical+Approach
	*/
	U64 attacks = initialAttacks[square];
	U64 blockers = attacks & board.both;
	int blockSquare;
	if (blockers) {
		if (direction == POSITIVE) blockSquare = bitScanForward(blockers);
		else blockSquare = bitScanReverse(blockers);
		attacks ^= initialAttacks[blockSquare];
		if (!includeAttacks && (contains(square, board.white) && contains(blockSquare, board.white) ||
			contains(square, board.black) && contains(blockSquare, board.black))) {
			clearBit(blockSquare, attacks);
		}
	}
	return attacks;
}

U64 getPawnAttacks(U64 pawns, string color) {
	U64 attacks = 0ULL;
	while (pawns) {
		int square = bitScanForward(pawns);
		if (color == WHITE) attacks |= whitePawnAttacks[square];
		else attacks |= blackPawnAttacks[square];
		clearBit(square, pawns);
	}
	return attacks;
}

U64 getAttacks(S_BOARD &board, string color) {
	assert(color == WHITE || color == BLACK);
	U64 attacks = 0ULL;
	if (color == WHITE) {
		attacks |= pieceAttacks(board, board.wR, "white", generateRookMoves);
		attacks |= pieceAttacks(board, board.wN, "white", generateKnightMoves);
		attacks |= pieceAttacks(board, board.wB, "white", generateBishopMoves);
		attacks |= pieceAttacks(board, board.wQ, "white", generateQueenMoves);
		U64 kingMoves = pieceAttacks(board, board.wK, "white", generateKingMoves);
		if (contains(E1, board.wK)) {
			clearBit(C1, kingMoves);
			clearBit(G1, kingMoves);
		}
		attacks |= kingMoves;
		attacks |= getPawnAttacks(board.wP, WHITE);
	}
	else {
		attacks |= pieceAttacks(board, board.bR, "black", generateRookMoves);
		attacks |= pieceAttacks(board, board.bN, "black", generateKnightMoves);
		attacks |= pieceAttacks(board, board.bB, "black", generateBishopMoves);
		attacks |= pieceAttacks(board, board.bQ, "black", generateQueenMoves);
		U64 kingMoves = pieceAttacks(board, board.bK, "black", generateKingMoves);
		if (contains(E8, board.bK)) {
			clearBit(C8, kingMoves);
			clearBit(G8, kingMoves);
		}
		attacks |= kingMoves;
		attacks |= getPawnAttacks(board.bP, BLACK);
	}
	return attacks;
}

U64 pieceAttacks(S_BOARD &board, U64 pieces, string color, U64 (*genFunc)(int, S_BOARD&, string, bool)) {
	U64 attacks = 0ULL;
	while (pieces) {
		int square = bitScanForward(pieces);
		attacks |= genFunc(square, board, color, true);
		clearBit(square, pieces);
	}
	return attacks;
}
































