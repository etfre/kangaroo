#ifndef DEFS_H
#define DEFS_H

#include <map>
#include <string>
#include <vector>

using namespace std;

typedef unsigned long long U64;
#define C64(constantU64) constantU64##ULL

typedef struct {
    /* colours */
    U64 white = 0ULL;
    U64 black = 0ULL;
    U64 both = 0ULL;

    /* white pieces */
    U64 wP = 0ULL;
    U64 wN = 0ULL;
    U64 wB = 0ULL;
    U64 wR = 0ULL;
    U64 wQ = 0ULL;
    U64 wK = 0ULL;
    vector<U64*> whiteList;

    /* black pieces */
    U64 bP = 0ULL;
    U64 bN = 0ULL;
    U64 bB = 0ULL;
    U64 bR = 0ULL;
    U64 bQ = 0ULL;
    U64 bK = 0ULL;
    vector<U64*> blackList;

    /* other */
    U64 wAttacks = 0ULL;
    U64 bAttacks = 0ULL;
} S_BOARD;

typedef struct {
    int fromSquare;
    int toSquare;
    double evaluation;
    U64 *pieces;
} S_MOVE;


/* FUNCTIONS */

// board
S_BOARD createBitboards(string stringBoard);
void movePiece(S_MOVE &move, S_BOARD &board, string color);
void clearPiece(int square, S_BOARD &board, string color);
void printBitboard(U64 bitBoard);
void printBoard(S_BOARD board);

// movegen
void generatePieceMoves(vector<S_MOVE> &possibleMoves, S_BOARD board, U64 &pieces, string color, U64 (*genFunc)(int, S_BOARD&, string, bool));
U64 generateRookMoves(int bitpos, S_BOARD &board, string color, bool includeAttacks);
U64 generateKnightMoves(int bitpos, S_BOARD &board, string color, bool includeAttacks);
U64 generateBishopMoves(int square, S_BOARD &board, string color, bool includeAttacks);
U64 generateQueenMoves(int square, S_BOARD &board, string color, bool includeAttacks);
U64 generateKingMoves(int square, S_BOARD &board, string color, bool includeAttacks);
U64 generatePawnMoves(int square, S_BOARD &board, string color, bool includeAttacks);
U64 getRayAttacks(int square, const U64 initialAttacks[64], S_BOARD &board, string direction, bool includeAttacks);
U64 getPawnAttacks(U64 pawns, string color);
U64 getAttacks(S_BOARD &board, string color);
U64 pieceAttacks(S_BOARD &board, U64 pieces, string color, U64 (*genFunc)(int, S_BOARD&, string, bool));

// bitops
int bitScanForward(U64 &bb);
int bitScanReverse(U64 &bb);
U64 toInt(string bitString);
string toString(U64 bitBoard);
void setBit(int position, U64 &bitString);
void clearBit(int position, U64 &bitString);
void toggleBit(int position, U64 &bitString);
void setBit(int square, U64 &pieces, S_BOARD &board, string color);
void clearBit(int square, U64 &pieces, S_BOARD &board);
void setAndClear(int fromSquare, int toSquare, U64 &pieces, S_BOARD &board, string color);
bool contains(int square, U64 bitstring);
vector<int> toSquaresfromBitboard(U64 bitstring);
int popCount(U64 bb);

// utilities
string switchColor(string color);

/* GLOBAL CONSTANTS */

enum directions {N, NE, E, SE, S, SW, W, NW};
const string POSITIVE = "positive";
const string NEGATIVE = "negative";

// players
const string WHITE = "white";
const string BLACK = "black";

// boards
const U64 FULL = 18446744073709551615ULL;
const U64 EMPTY = 0ULL;

// ranks
const U64 RANK1 = 255ULL;
const U64 RANK2 = 65280ULL;
const U64 RANK3 = 16711680ULL;
const U64 RANK4 = 4278190080ULL;
const U64 RANK5 = 1095216660480ULL;
const U64 RANK6 = 280375465082880ULL;
const U64 RANK7 = 71776119061217280ULL;
const U64 RANK8 = 18374686479671623680ULL;
// files
const U64 AFILE = 72340172838076673ULL;
const U64 BFILE = 144680345676153346ULL;
const U64 CFILE = 289360691352306692ULL;
const U64 DFILE = 578721382704613384ULL;
const U64 EFILE = 1157442765409226768ULL;
const U64 FFILE = 2314885530818453536ULL;
const U64 GFILE = 4629771061636907072ULL;
const U64 HFILE = 9259542123273814144ULL;
// squares
const int A1 = 0;
const int B1 = 1;
const int C1 = 2;
const int D1 = 3;
const int E1 = 4;
const int F1 = 5;
const int G1 = 6;
const int H1 = 7;
const int A2 = 8;
const int B2 = 9;
const int C2 = 10;
const int D2 = 11;
const int E2 = 12;
const int F2 = 13;
const int G2 = 14;
const int H2 = 15;
const int A3 = 16;
const int B3 = 17;
const int C3 = 18;
const int D3 = 19;
const int E3 = 20;
const int F3 = 21;
const int G3 = 22;
const int H3 = 23;
const int A4 = 24;
const int B4 = 25;
const int C4 = 26;
const int D4 = 27;
const int E4 = 28;
const int F4 = 29;
const int G4 = 30;
const int H4 = 31;
const int A5 = 32;
const int B5 = 33;
const int C5 = 34;
const int D5 = 35;
const int E5 = 36;
const int F5 = 37;
const int G5 = 38;
const int H5 = 39;
const int A6 = 40;
const int B6 = 41;
const int C6 = 42;
const int D6 = 43;
const int E6 = 44;
const int F6 = 45;
const int G6 = 46;
const int H6 = 47;
const int A7 = 48;
const int B7 = 49;
const int C7 = 50;
const int D7 = 51;
const int E7 = 52;
const int F7 = 53;
const int G7 = 54;
const int H7 = 55;
const int A8 = 56;
const int B8 = 57;
const int C8 = 58;
const int D8 = 59;
const int E8 = 60;
const int F8 = 61;
const int G8 = 62;
const int H8 = 63;

	
#endif