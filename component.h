#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "common.h"
using namespace std;

const string INDEX = "Index";
const string TAPE = "Tape";
const string HEAD = "Head";

class Tape
{
private:
    char mspace;
    string tape;
    int head;   // read-write head
    int front;  // to locate where to write on tape_string
                // pos = head - front
public:
    Tape(char setspace = SPACE, string input = string()) : mspace(setspace), head(0), front(0), tape(input) {}

    int getHead() const;
    string getTape() const;
    void setInput(string input);
    // return symbol at head on the tape
    char read();
    // return symbol at target on the tape
    char charAt(int target);
    // set symbol at head and move head according to direc
    void write(char symbol, char direc);
    // return verbose_string, tape_cnt passed for alignment
    string verbose(int tape_index, int tape_cnt);
};

class TKey  // to store transition
{
public:
    string state;   // old state id
    string symbol;  // current symbol

    TKey() {}
    TKey(string _state, string _symbol) : state(_state), symbol(_symbol) {}

    bool operator<(const TKey &t) const;  // Map Key
    bool operator>(const TKey &t) const;  // Map Key
};

class TValue  // to store transition
{
public:
    string state;  // new state
    string write;  // symbol to write
    string direc;  // direction

    TValue() {}
    TValue(string _state, string _write, string _direc) : state(_state), write(_write), direc(_direc) {}
};

#endif