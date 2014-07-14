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
};

#endif