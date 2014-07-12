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
	// S_BOARD board;
	// Position pos(S_BOARD b, string c);
	TestClass();
	void testDefaultSetup();
	void testPin1();
};

#endif