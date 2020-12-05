#include "util.h"

using namespace std;

string removeComment(string s)
{
    int cmt_idx = s.find(';');
    if (cmt_idx != string::npos)
        s = string(s, 0, cmt_idx);
    return s;
}

string strip(string s)
{
    int st = 0, ed = s.length();
    for (int i = 0; i < s.length(); i++)
    {
        if (!isspace(s[i]))
        {
            st = i;
            break;
        }
    }
    for (int i = s.length() - 1; i >= 0; i--)
    {
        if (!isspace(s[i]))
        {
            ed = i + 1;
            break;
        }
    }
    return string(s, st, ed - st);
}

vector<Match> split(string s, string re)
{
    string origin(s);
    regex tok(re);
    smatch match;
    vector<Match> ret;
    int begin = 0;
    while (regex_search(s, match, tok))
    {
        ret.push_back(Match(match.prefix(), begin));
        s = match.suffix();
        begin = origin.length() - s.length();
    }
    ret.push_back(Match(s, begin));
    return ret;
}

bool isValidState(string state)
{
    if (state.empty())
        return false;
    for (auto c : state)
    {
        if (('a' <= c && c <= 'z') ||
            ('A' <= c && c <= 'Z') ||
            ('0' <= c && c <= '9') ||
            c == '_')
            continue;
        else
            return false;
    }
    return true;
}

bool isValidInputSymbol(char symbol)
{
    return !(symbol == ' ' || symbol == ',' || symbol == ';' || symbol == '*' || symbol == '_');
}

bool isValidTapeSymbol(char symbol)
{
    return !(symbol == ' ' || symbol == ',' || symbol == ';' || symbol == '*');
}

bool isValidDirec(char direc)
{
    return (direc == LEFT || direc == RIGHT || direc == STAY);
}

string quote(string q, string s)
{
    return "'" + q + "' " + s;
}
string quote(char q, string s)
{
    return "'" + string(1, q) + "' " + s;
}

size_t findRightmostFromLeft(string s, char c)
{
    int i = 0;
    if (s[i] != c)
        return string::npos;
    while (i < s.length() && s[i] == c)
    {
        i++;
    }
    return i - 1;
}
size_t findLeftmostFromRight(string s, char c)
{
    int i = s.length() - 1;
    if (s[i] != c)
        return string::npos;
    while (i >= 0 && s[i] == c)
    {
        i--;
    }
    return i + 1;
}