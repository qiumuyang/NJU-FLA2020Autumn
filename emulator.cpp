#include "emulator.h"

string Emulator::getTapeCombined()
{
    char ch;
    string ret;
    for (auto iter : tapes)
    {
        ch = iter.read();
        ret += string(1, ch);
    }
    return ret;
}
void Emulator::writeTapeCombined(string write, string direc)
{
    for (int i = 0; i < tapes.size(); i++)
    {
        tapes[i].write(write[i], direc[i]);
    }
}

// no error handling here
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
    tape_cnt = cnt;
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

int Emulator::getTapeCount() const
{
    return tape_cnt;
}
bool Emulator::containsState(string nstate) const
{
    return (states.find(nstate) != states.end());
}
bool Emulator::containsInputSymbol(char symbol) const
{
    return (i_symbols.find(symbol) != i_symbols.end());
}
bool Emulator::containsTapeSymbol(char symbol) const
{
    return (t_symbols.find(symbol) != t_symbols.end());
}
bool Emulator::containsTransition(string ostate, string input) const
{
    return (transition.find(TKey(ostate, input)) != transition.end());
}

string Emulator::execute(bool isVerbose)
{
    int step = 0;
    while (true)
    {
        if (isVerbose)
            cout << verbose(step);
        TKey current = TKey(cstate, getTapeCombined());
        if (f_states.find(cstate) != f_states.end())
        {
            break;  // reach final state
        }
        auto result = transition.find(current);
        if (result == transition.end())
        {
            break;  // no next transition
        }
        TValue next = result->second;
        cstate = next.state;
        writeTapeCombined(next.write, next.direc);
        step++;
    }
    if (isVerbose)
        cout << result();
    return tapes[0].getTape();
}
string Emulator::verbose(int step)
{
    string tape_str;
    for (int i = 0; i < tapes.size(); i++)
    {
        tape_str += tapes[i].verbose(i, tape_cnt);
    }
    int width = to_string(tape_cnt - 1).length() + INDEX.length() + 1;
    stringstream ss_step;
    stringstream ss_state;
    ss_step << setiosflags(ios::left);
    ss_step << setw(width) << "Step"
            << ": " << step << '\n';
    ss_state << setiosflags(ios::left);
    ss_state << setw(width) << "State"
             << ": " << cstate << '\n';
    return ss_step.str() + tape_str + ss_state.str() + STEP_SPLITTER + "\n";
}
string Emulator::result()
{
    int width = to_string(tape_cnt - 1).length() + INDEX.length() + 1;
    stringstream ss_result;
    ss_result << setiosflags(ios::left);
    ss_result << setw(width) << "Result"
              << ": " << tapes[0].getTape() << '\n';
    return ss_result.str();
}