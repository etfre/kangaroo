#ifndef TESTS_H
#define TESTS_H
#include <vector>
#include <string>

#include "../include/defs.h"
#include "../include/position.h"

using namespace std;

class TestClass
{
public:
	TestClass();
	void testDefaultSetup();
	void testPin1();
	void testMateInOne1();
	void testStartingStalemateWhite();
	void testStartingStalemateBlack();
	void testStartingCheckmateWhite();
	void testStartingCheckmateBlack();
	void testAnyLegalMoves1();
	void testNoLegalMoves();
	void testAnyLegalMoves2();
	void testMateInTwo1();
	void testForcedStalemate1();
};

#endif