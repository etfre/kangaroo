#ifndef TESTBOARDS_H
#define TESTBOARDS_H

#include <string>
#include "../include/defs.h"

using namespace std;

const string defaultBoard = "R N B Q K B N R"
                            "P P P P P P P P"
                            "_ _ _ _ _ _ _ _"
                            "_ _ _ _ _ _ _ _"
                            "_ _ _ _ _ _ _ _"
                            "_ _ _ _ _ _ _ _"
                            "p p p p p p p p"
                            "r n b q k b n r"
                            ;

const string testPinBoard1 = "_ _ _ _ _ _ _ _"
                             "_ _ _ _ _ K _ _"
                             "_ _ _ _ R _ _ _"
                             "_ _ _ _ _ _ _ _"
                             "_ _ _ _ _ _ _ _"
                             "_ _ _ b _ _ _ _"
                             "_ k _ _ _ _ _ _"
                             "_ _ _ _ _ _ _ _"
                             ;

const string testMateInOneBoard1 = "K _ _ _ _ _ _ _"
                                   "_ _ _ _ _ _ _ r"
                                   "k _ _ _ _ _ _ _"
                                   "_ _ _ _ _ _ _ _"
                                   "_ _ _ _ _ _ _ _"
                                   "_ _ _ _ _ _ _ _"
                                   "_ _ _ _ _ _ _ _"
                                   "_ _ _ _ _ _ _ _"
                                   ;

const string testStartingStalemateWhiteBoard = "k _ K _ _ _ _ _"
                                               "_ _ _ _ _ _ _ R"
                                               "_ _ _ _ _ _ _ _"
                                               "_ _ _ _ _ _ _ _"
                                               "_ _ _ _ _ _ _ _"
                                               "_ _ _ _ _ _ _ _"
                                               "_ _ _ _ _ _ _ _"
                                               "_ _ _ _ _ _ _ _"
                                               ;

const string testStartingStalemateBlackBoard = "K _ k _ _ _ _ _"
                                               "_ _ _ _ _ _ _ r"
                                               "_ _ _ _ _ _ _ _"
                                               "_ _ _ _ _ _ _ _"
                                               "_ _ _ _ _ _ _ _"
                                               "_ _ _ _ _ _ _ _"
                                               "_ _ _ _ _ _ _ _"
                                               "_ _ _ _ _ _ _ _"
                                               ;

const string testStartingCheckmateWhiteBoard = "R _ k _ _ _ _ _"
                                               "_ _ _ _ _ _ _ _"
                                               "_ _ K _ _ _ _ _"
                                               "_ _ _ _ _ _ _ _"
                                               "_ _ _ _ _ _ _ _"
                                               "_ _ _ _ _ _ _ _"
                                               "_ _ _ _ _ _ _ _"
                                               "_ _ _ _ _ _ _ _"
                                               ;

const string testStartingCheckmateBlackBoard = "_ _ K _ q _ _ _"
                                               "_ _ _ _ _ _ _ _"
                                               "_ _ k _ _ _ _ _"
                                               "_ _ _ _ _ _ _ _"
                                               "_ _ _ _ _ _ _ _"
                                               "_ _ _ _ _ _ _ _"
                                               "_ _ _ _ _ _ _ _"
                                               "_ _ _ _ _ _ _ _"
                                               ;

const string testAnyLegalMovesBoard = "K _ _ _ _ _ _ _"
                                      "_ _ _ _ _ _ _ _"
                                      "k _ _ b _ _ _ _"
                                      "_ _ _ _ _ _ _ P"
                                      "_ _ _ _ _ _ _ p"
                                      "_ _ _ _ _ _ _ _"
                                      "_ _ _ _ _ _ _ _"
                                      "_ _ _ _ _ _ _ _"
                                      ;

#endif