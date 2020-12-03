#ifndef __UTIL_H__
#define __UTIL_H__

#include <regex>
#include <string>
#include <vector>

#include "const.h"

using namespace std;

class Match
{
public:
    string str;
    int start;
    Match(string s, int b) : str(s), start(b) {}
};

string removeComment(string s);
string strip(string s);
vector<Match> split(string s, string re);

bool isValidState(string state);
bool isValidInputSymbol(char symbol);
bool isValidTapeSymbol(char symbol);
bool isValidDirec(char direc);

string quote(string q, string s);
string quote(char q, string s);

#endif