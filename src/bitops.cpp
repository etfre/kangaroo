#include <iostream>
#include <vector>
#include <assert.h>
#include "../include/defs.h"

using namespace std;

const int index64[64] = {
    0, 47,  1, 56, 48, 27,  2, 60,
   57, 49, 41, 37, 28, 16,  3, 61,
   54, 58, 35, 52, 50, 42, 21, 44,
   38, 32, 29, 23, 17, 11,  4, 62,
   46, 55, 26, 59, 40, 36, 15, 53,
   34, 51, 20, 43, 31, 22, 10, 45,
   25, 39, 14, 33, 19, 30,  9, 24,
   13, 18,  8, 12,  7,  6,  5, 63
};

int bitScanForward(U64 &bb) {
  //Return the index of the least significant bit in an int
   const U64 debruijn64 = C64(0x03f79d71b4cb0a89);
   assert (bb != 0);
   return index64[((bb ^ (bb-1)) * debruijn64) >> 58];
}

int bitScanReverse(U64 &bb) {
  //Return the index of the most significant bit in an int
   const U64 debruijn64 = C64(0x03f79d71b4cb0a89);
   assert (bb != 0);
   bb |= bb >> 1; 
   bb |= bb >> 2;
   bb |= bb >> 4;
   bb |= bb >> 8;
   bb |= bb >> 16;
   bb |= bb >> 32;
   return index64[(bb * debruijn64) >> 58];
}

U64 toInt(string bitString){
	assert(bitString.size() == 64);
    int tempInt;
    U64 num=0ULL;
    for(int i=0; i<64; i++){
        tempInt=bitString[i]-'0';
        num |= (1ULL << (63-i)) * tempInt;
    }
    return num;
}

string toString(U64 bitBoard) {
  char result[(sizeof(U64) * 8) + 1];
  unsigned index  = sizeof(U64) * 8;
  result[index] = '\0';
  do result[ --index ] = '0' + (bitBoard & 1);
  while (bitBoard >>= 1);
  string zeroes = string(index, '0');
  assert((zeroes + string(result + index)).size() == 64);
  return zeroes + string(result + index);
}

void setBit(int position, U64 &bitString) {
	bitString |= 1ULL << position;
}

void clearBit(int position, U64 &bitString) {
	bitString &= ~(1ULL << position);
}

void toggleBit(int position, U64 &bitString) {
	bitString ^= 1ULL << position;
}

void setAndClear(int fromSquare, int toSquare, U64 &pieces, S_BOARD &board, string color) {
	clearBit(fromSquare, pieces, board);
	setBit(toSquare, pieces, board, color);
 }

void setBit(int square, U64 &pieces, S_BOARD &board, string color) {
	if (color == WHITE) {
		board.white |= 1ULL << square;
	}
	else if (color == BLACK) {
		board.black |= 1ULL << square;
	}
	pieces |= 1ULL << square;
	board.both = board.white | board.black;
}

void clearBit(int square, U64 &pieces, S_BOARD &board) {
	if (pieces & board.white) {
		board.white &= ~(1ULL << square);
	}
	else if (pieces & board.black) {
		board.black &= ~(1ULL << square);
	}
	pieces &= ~(1ULL << square);
	board.both = board.white | board.black;
}

bool contains(int square, U64 bitstring) {
    return (bitstring & (1ULL << square)) != 0;
}

vector<int> toSquaresfromBitboard(U64 bitstring) {
	vector<int> toSquares;
	while (bitstring != 0) {
		int square = bitScanForward(bitstring);
		toSquares.push_back(square);
		clearBit(square, bitstring);
	}
  return toSquares;
}

int popCount(U64 bb) {
    int count;
    for (count=0; bb; count++)
        bb &= bb - 1;
    return count;
}








