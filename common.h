#ifndef __COMMON_H__
#define __COMMON_H__

#include <assert.h>

#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

constexpr char LEFT = 'l';
constexpr char RIGHT = 'r';
constexpr char STAY = '*';
constexpr char SPACE = '_';  // assume all spaces in this experiment are '_' (FROM MANUAL)

constexpr int TO_LEFT = 1;
constexpr int TO_RIGHT = 2;
constexpr int BETWEEN = 3;

const std::string STATUS_SPLITTER = "====================";

#endif