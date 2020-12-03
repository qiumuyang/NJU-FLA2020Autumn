#include "turing.h"

using namespace std;

void Turing::load_file()
{
    ifstream in(file);
    if (!in)
        throw TuringException(FILE_NOT_FOUND, 0, quote(file, "open failed"));
    string line;
    while (getline(in, line))
    {
        line = removeComment(line);
        line = strip(line);
        if (!line.empty())
            lines.push_back(line);
    }
}

void Turing::verify_input()
{
    for (int i = 0; i < input.length(); i++)
    {
        if (!emulator.containsInputSymbol(input[i]))
        {
            throw TuringException(ILLEGAL_INPUT, i, quote(input[i], "was not declared in the set of input symbols"));
        }
    }
}

int Turing::execute(bool verbose)
{
    if (verbose)
        cout << "Input: " << input << endl;

    try
    {
        load_file();
        for (auto line : lines)
        {
            current_line = line;
            parser.parseLine(line);
        }
        cout << "parse end" << endl;
        emulator = parser.getTuringEmulator();
        cout << "get emulator" << endl;
        verify_input();
        cout << "input verified" << endl;
        emulator.setInput(input);
    }
    catch (const TuringException& e)
    {
        handleExceptionPrint(verbose, e);
        return -1;
    }
    catch (const exception& e)
    {
        cerr << e.what() << endl;
        return -1;
    }

    if (verbose)
        cout << STATUS_SPLITTER << " RUN " << STATUS_SPLITTER << endl;
    string ret = emulator.execute(verbose);
    if (verbose)
        cout << STATUS_SPLITTER << " END " << STATUS_SPLITTER << endl;
    else
        cout << ret << endl;

    return 0;
}

void Turing::handleExceptionPrint(bool verbose, const TuringException& e)
{
    if (verbose)
    {
        cout << STATUS_SPLITTER << " ERR " << STATUS_SPLITTER << endl;
        switch (e.type())
        {
        case FILE_NOT_FOUND:
            cout << e.what_verbose() << endl;
            break;
        case ILLEGAL_INPUT:
            cout << e.what_verbose() << endl;
            cout << "Input: " << input << endl;
            cout << setw(7 + e.position()) << "^" << endl;
            break;
        default:
            cout << e.what_verbose() << endl;
            cout << "Line: " << current_line << endl;
            cout << setw(6 + e.position()) << "^" << endl;
            break;
        }
        cout << STATUS_SPLITTER << " END " << STATUS_SPLITTER << endl;
    }
    else
    {
        cerr << e.what() << endl;
    }
}