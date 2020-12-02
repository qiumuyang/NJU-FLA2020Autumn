#include <vector>
#include <set>
#include <string>
#include <map>
#include "component.h"
using namespace std;

class Emulator
{
private:
    set<string> states;
    set<string> f_states; // final states
    set<char> i_symbols;  // input symbols
    set<char> t_symbols;  // tape symbols
    int state;            // current state
    char space;
    int tape_cnt;
    vector<Tape> tapes;

public:
    Emulator();
};