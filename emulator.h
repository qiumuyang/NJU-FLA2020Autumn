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

    bool containsState(string nstate);
    bool containsInputSymbol(char symbol);
    bool containsTapeSymbol(char symbol);
    bool containsTransition(string ostate, string input);
};

#endif