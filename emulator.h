#ifndef __EMULATOR_H__
#define __EMULATOR_H__

#include <map>
#include <set>
#include <string>
#include <vector>

#include "component.h"

using namespace std;

const string STEP_SPLITTER = string(46, '-');

class Emulator
{
private:
    set<string> states;
    set<string> f_states;  // final states
    set<char> i_symbols;   // input symbols
    set<char> t_symbols;   // tape symbols
    string cstate;         // current state
    char space;
    int tape_cnt;
    vector<Tape> tapes;
    map<TKey, TValue> transition;

    string getTapeCombined();
    void writeTapeCombined(string write, string direc);
    void checkIntegrity();

public:
    Emulator() : space(SPACE) {}
    void addState(string nstate);
    void addFinalState(string nfstate);
    void addInputSymbol(char symbol);
    void addTapeSymbol(char symbol);
    void setCurrentState(string nstate);
    void setSpace(char nspace);
    void setTape(int cnt);
    void setInput(string input);
    void addTransition(string ostate, string input, string nstate, string write, string direc);

    int getTapeCount() const;
    bool containsState(string nstate) const;
    bool containsInputSymbol(char symbol) const;
    bool containsTapeSymbol(char symbol) const;
    bool containsTransition(string ostate, string input) const;

    string execute(bool isVerbose = false);
    string verbose(int step);
    string result();
};

#endif