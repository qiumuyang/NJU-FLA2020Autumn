#ifndef __PARSER_H__
#define __PARSER_H__

#include <regex>

#include "common.h"
#include "emulator.h"

// construct a Turing Emulator by passing in lines of file
class Parser
{
private:
    int align;

    Emulator emulator;
    void parseSingle(string type, string str);
    void parseMulti(string type, string str);
    void parseTransition(string str);
    void checkMultiDefinition(string component);

    set<string> parsed;

public:
    Parser() {}

    // read file line by line, and call this func multiple times
    // line should be removed comments, stripped and ensured not empty
    // Caution : catch exception
    void parseLine(string line);
    // get the constructed Emulator
    Emulator& getTuringEmulator() { return emulator; }
};

#endif