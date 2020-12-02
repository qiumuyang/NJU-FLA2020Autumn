#include "emulator.h"

void Emulator::addState(string nstate)
{
    states.insert(nstate);
}
void Emulator::addFinalState(string nfstate)
{
    states.insert(nfstate);
}
void Emulator::addInputSymbol(char symbol)
{
    i_symbols.insert(symbol);
}
void Emulator::addTapeSymbol(char symbol)
{
    t_symbols.insert(symbol);
}
void Emulator::setCurrentState(string nstate)
{
    cstate = nstate;
}
void Emulator::setSpace(char nspace)
{
    space = nspace;
}
void Emulator::setTape(int cnt)
{
    for (int i = 0; i < cnt; i++)
    {
        tapes.push_back(Tape(space));
    }
}
void Emulator::setInput(string input)
{
    tapes[0].setInput(input);
}
void Emulator::addTransition(string ostate, string input, string nstate, string write, string direc)
{
    transition[TKey(ostate, input)] = TValue(nstate, write, direc);
}

bool Emulator::containsState(string nstate)
{
    return (states.find(nstate) != states.end());
}
bool Emulator::containsInputSymbol(char symbol)
{
    return (i_symbols.find(symbol) != i_symbols.end());
}
bool Emulator::containsTapeSymbol(char symbol)
{
    return (t_symbols.find(symbol) != t_symbols.end());
}
bool Emulator::containsTransition(string ostate, string input)
{
    return (transition.find(TKey(ostate, input)) != transition.end());
}