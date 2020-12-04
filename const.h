#ifndef __CONST_H__
#define __CONST_H__

#include <string>

constexpr char LEFT = 'l';
constexpr char RIGHT = 'r';
constexpr char STAY = '*';
constexpr char SPACE = '_';  // assume all spaces in this experiment are '_' (FROM MANUAL)

constexpr int TO_LEFT = 1;
constexpr int TO_RIGHT = 2;
constexpr int BETWEEN = 3;

const std::string STATUS_SPLITTER = "====================";

static const std::string err_msg[] = {"",
                                      "illegal input",
                                      "illegal state",
                                      "illegal symbol",
                                      "syntax error",
                                      "duplicated exception",
                                      "file not found"};
constexpr int ILLEGAL_INPUT = 1;
constexpr int ILLEGAL_STATE = 2;
constexpr int ILLEGAL_SYMBOL = 3;
constexpr int SYNTAX_ERROR = 4;
constexpr int DUPLICATED = 5;
constexpr int FILE_NOT_FOUND = 6;

const std::string usage = "usage: turing [-v|--verbose] [-h|--help] <tm> <input>";

#endif