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
    string tape;
    int head;   // read-write head
    int front;  // to locate where to write on tape_string
                // pos = head - front
public:
    Tape()
    {
        head = 0;
        front = 0;
    }

    int getHead() const;
    string getTape() const;
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

    bool operator<(const TKey &t) const;  // Map Key
    bool operator>(const TKey &t) const;  // Map Key
};

class TValue  // to store transition
{
public:
    string state;  // new state
    string write;  // symbol to write
    string direc;  // direction
};

#endif