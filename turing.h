#ifndef __TURING_H__
#define __TURING_H__

#include "common.h"
#include "parser.h"

using namespace std;

class Turing
{
private:
    string file;
    string input;
    vector<string> lines;
    string current_line;
    vector<int> line_ids;
    int current_line_id;

    Parser parser;
    Emulator emulator;

    void load_file();
    void verify_input();
    void handleExceptionPrint(bool verbose, const TuringException& e);

public:
    Turing(string path, string in) : file(path), input(in) {}

    int execute(bool verbose);
};

#endif