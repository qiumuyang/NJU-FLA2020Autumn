#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "common.h"
using namespace std;

class Tape
{
public:
    string tape;
    int head;  // read-write head
    int front; // to locate where to write on tape_string
               // pos = head - front

    Tape()
    {
        head = 0;
        front = 0;
    }

    char read();
    void write(char symbol, char direc);
    string verbose(int index);
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