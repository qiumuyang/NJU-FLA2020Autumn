#include "parser.h"

using namespace std;

void Parser::parseLine(string line)
{
    regex reMulti("^#(Q|S|G|F) *= *\\{ *(.*) *\\}$");
    regex reSingle("^#(q0|B|N) *= *(.*)$");
    smatch match;
    if (regex_match(line, match, reMulti))
    {
        align = match.position(2);
        parseMulti(match[1], match[2]);
    }
    else if (regex_match(line, match, reSingle))
    {
        align = match.position(2);
        parseSingle(match[1], match[2]);
    }
    else
    {
        align = 0;
        parseTransition(line);
    }
}
void Parser::parseMulti(string type, string str)
{
    vector<Match> ret = split(str, " *, *");
    checkMultiDefinition(type);
    switch (type[0])
    {
    case 'Q':
        for (auto m : ret)
        {
            if (!isValidState(m.str))
                throw TuringException(ILLEGAL_STATE, align + m.start, quote(m.str, "contains invalid character or is empty"));
            if (emulator.containsState(m.str))
                throw TuringException(DUPLICATED, align + m.start, quote(m.str, "already exists"));

            emulator.addState(m.str);
        }
        break;
    case 'S':
        for (auto m : ret)
        {
            if (m.str.length() != 1)
                throw TuringException(ILLEGAL_SYMBOL, align + m.start, quote(m.str, "is too long/short"));
            char symbol = m.str[0];
            if (!isValidInputSymbol(symbol))
                throw TuringException(ILLEGAL_SYMBOL, align + m.start, quote(symbol, "is an invalid character"));
            if (emulator.containsInputSymbol(symbol))
                throw TuringException(DUPLICATED, align + m.start, quote(symbol, "already exists"));

            emulator.addInputSymbol(symbol);
        }
        break;
    case 'G':
        for (auto m : ret)
        {
            if (m.str.length() != 1)
                throw TuringException(ILLEGAL_SYMBOL, align + m.start, quote(m.str, "is too long/short"));
            char symbol = m.str[0];
            if (!isValidTapeSymbol(symbol))
                throw TuringException(ILLEGAL_SYMBOL, align + m.start, quote(symbol, "is an invalid character"));
            if (emulator.containsTapeSymbol(symbol))
                throw TuringException(DUPLICATED, align + m.start, quote(symbol, "already exists"));

            emulator.addTapeSymbol(symbol);
        }
        break;
    case 'F':
        for (auto m : ret)
        {
            if (!emulator.containsState(m.str))
                throw TuringException(ILLEGAL_STATE, align + m.start, quote(m.str, "was not declared in the set of states"));

            emulator.addFinalState(m.str);
        }
        break;
    default:
        assert(0);
    }
}
void Parser::parseSingle(string type, string str)
{
    char symbol = 0;
    checkMultiDefinition(type);
    switch (type[0])
    {
    case 'q':
        if (!emulator.containsState(str))
            throw TuringException(ILLEGAL_STATE, align, quote(str, "was not declared in the set of states"));

        emulator.setCurrentState(str);
        break;
    case 'B':
        if (str.length() != 1)
            throw TuringException(ILLEGAL_SYMBOL, align, quote(str, "is too long/short"));
        symbol = str[0];
        if (!isValidTapeSymbol(symbol))
            throw TuringException(ILLEGAL_SYMBOL, align, quote(symbol, "is an invalid character"));
        if (emulator.containsInputSymbol(str[0]))
            throw TuringException(ILLEGAL_SYMBOL, align, quote(symbol, "is already in the set of input symbols"));

        emulator.setSpace(symbol);
        break;
    case 'N':
        if (!isdigit(*(str.c_str())))
            throw TuringException(SYNTAX_ERROR, align, "N should be a number");

        emulator.setTape(stoi(str));
        break;
    default:
        assert(0);
    }
}
void Parser::parseTransition(string str)
{
    vector<Match> ret = split(str, " +");
    if (ret.size() != 5)
        throw TuringException(SYNTAX_ERROR, ret.back().start, "transition format - <old state> <old symbols> <new symbols> <directions> <new state>");
    Match ostate = ret[0], nstate = ret[4];
    Match direc = ret[3];
    Match osym = ret[1], nsym = ret[2];
    if (!emulator.containsState(ostate.str))
        throw TuringException(ILLEGAL_STATE, align + ostate.start, quote(ostate.str, "was not declared in the set of states"));
    if (!emulator.containsState(nstate.str))
        throw TuringException(ILLEGAL_STATE, align + nstate.start, quote(nstate.str, "was not declared in the set of states"));
    int cnt = emulator.getTapeCount();
    if (osym.str.length() != cnt)
        throw TuringException(SYNTAX_ERROR, align + osym.start, quote(osym.str, "does not match the number of tapes"));
    if (nsym.str.length() != cnt)
        throw TuringException(SYNTAX_ERROR, align + nsym.start, quote(nsym.str, "does not match the number of tapes"));
    if (direc.str.length() != cnt)
        throw TuringException(SYNTAX_ERROR, align + direc.start, quote(direc.str, "does not match the number of tapes"));
    for (int i = 0; i < cnt; i++)
    {
        if (!emulator.containsTapeSymbol(osym.str[i]))
            throw TuringException(ILLEGAL_SYMBOL, align + osym.start + i, quote(osym.str[i], "was not declared in the set of tape symbols"));
        if (!emulator.containsTapeSymbol(nsym.str[i]))
            throw TuringException(ILLEGAL_SYMBOL, align + nsym.start + i, quote(nsym.str[i], "was not declared in the set of tape symbols"));
        if (!isValidDirec(direc.str[i]))
            throw TuringException(SYNTAX_ERROR, align + direc.start + i, quote(direc.str[i], "is an invalid direction"));
    }
    emulator.addTransition(ostate.str, osym.str, nstate.str, nsym.str, direc.str);
}
void Parser::checkMultiDefinition(string component)
{
    if (parsed.find(component) == parsed.end())
    {
        parsed.insert(component);
    }
    else
    {
        throw TuringException(SYNTAX_ERROR, 1, quote(component, "is multiple defined"));
    }
}