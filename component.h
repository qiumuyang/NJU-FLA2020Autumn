#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "common.h"
using namespace std;

class Tape
{
public:        // TODO: make it private
    string tape;
    int head;  // read-write head
    int front; // to locate where to write on tape_string
               // pos = head - front

    Tape()
    {
        head = 0;
        front = 0;
    }

    // return symbol at head on the tape
    char read();
    // set symbol at head and move head according to direc
    void write(char symbol, char direc);
    // return verbose_string, tape_cnt passed for alignment
    string verbose(int tape_index, int tape_cnt);
};

class TKey // to store transition
{
public:
    string state;  // old state id
    string symbol; // current symbol

    bool operator<(const TKey &t) const; // Map Key
    bool operator>(const TKey &t) const; // Map Key
};

class TValue // to store transition
{
public:
    string state; // new state
    string write; // symbol to write
    string direc; // direction
};

#endif