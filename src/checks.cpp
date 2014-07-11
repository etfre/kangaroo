#include <iostream>
#include <assert.h>
#include <vector>
#include "../include/defs.h"

using namespace std;

void checkBoard(S_BOARD &board) {
	/*
	Make sure none of the piece bitboards overlap, that the white and black
	bitboards are comprised exclusively of their respective pieces, and
	that the both bitboard is white OR black.
	*/
	vector<U64> pieces = {board.wR, board.wN, board.wB, board.wQ, board.wK,
						  board.wP, board.bR, board.bN, board.bB, board.bQ,
						  board.bK, board.bP};
	for (int i = 0; i < pieces.size()-1; i++) {
		for(int j = i+1; j < pieces.size(); j++) {
			assert(!(pieces[i] & pieces[j]));
		}
	}
	// assert(popCount(board.wK) == 1 && popCount(board.bK) == 1);
	assert((board.wR | board.wN | board.wB | board.wQ | board.wK | board.wP) == board.white);
	assert((board.bR | board.bN | board.bB | board.bQ | board.bK | board.bP) == board.black);
	assert((board.white | board.black) == board.both);
}